# STS GameplayTag 分级设计

## 定义在哪

| 位置 | 作用 |
|------|------|
| [`Plugins/STSFramework/Config/Tags/STSGameplayTags.ini`](../unrealSTS/Plugins/STSFramework/Config/Tags/STSGameplayTags.ini) | **主注册表**：编辑器 GameplayTag 面板、DataAsset 下拉、策划可见 |
| [`Plugins/STSFramework/.../STSGameplayTags.h`](../unrealSTS/Plugins/STSFramework/Source/STSFramework/Public/Core/STSGameplayTags.h) | **C++ 原生 Tag**：`STSGameplayTags::Card_Type_Attack`，避免硬编码字符串 |
| [`Config/DefaultGameplayTags.ini`](../unrealSTS/Config/DefaultGameplayTags.ini) | 工程入口：`ImportTagsFromConfig` 把插件 INI 导入引擎 |

**约定：** 新增 Tag 时 **INI 与 C++ 同步**；前缀统一 **`STS.`**，不再使用无前缀的 `Relic.Trigger` 等写法。

**层级规则：** UE 按点号自动建立父子关系。例如 `STS.Card.Type.Attack` 隐含父 Tag `STS.Card.Type`、`STS.Card`、`STS`。查询时可用 `HasTag(STS.Card)` 匹配所有卡牌相关 Tag。

---

## 分级总览

```text
STS
├── Card
│   ├── Type.*          攻击/技能/能力/状态/诅咒
│   ├── Rarity.*        Basic/Common/Uncommon/Rare
│   ├── Pool.*          角色卡池（Ironclad、Colorless…）
│   ├── State.*         运行时升级状态
│   └── Keyword.*       消耗/虚无/保留…
├── Status
│   ├── *               Buff 标识（易伤、力量…）
│   └── Decay.*         层数衰减时机
├── Phase.*             玩家回合 / 敌人回合（GA 门控）
├── Event
│   ├── Combat.*        战斗开始/胜/败 → HandleGameplayEvent
│   ├── Turn.*          回合边界事件
│   └── Card.*          打出牌
├── Relic
│   └── Trigger.*       遗物 DataAsset 触发条件（映射到 Event）
├── Action.*            通用 GA 的 ActionTag（AbilitySet）
├── Data.*              GE SetByCaller 键名
├── Granted
│   └── Power           能力牌已打出（子 Tag 运行时拼接 CardId）
└── UI
    └── Layer.*         CommonUI 四层栈
```

---

## 各类 Tag 用途

### STS.Card.*

| 子树 | 示例 | 谁用 |
|------|------|------|
| `Type` | `Attack`, `Skill`, `Power` | `USTSCardData.CardTypeTag`、遗物 Filter、UI 边框 |
| `Rarity` | `Common`, `Rare` | 奖励权重、商店 |
| `Pool` | `Ironclad`, `Colorless` | 战后三选一卡池筛选 |
| `State` | `Upgraded`, `CombatUpgrade` | `FSTSCardInstance` 与效果分支 |
| `Keyword` | `Exhaust`, `Ethereal` | `GA_PlayCard`、弃牌逻辑 |

### STS.Status.*

| Tag | 用途 |
|-----|------|
| `Vulnerable` / `Weak` / `Poison` / `Strength` | GE **Granted Tag**；伤害 Execution 读取 |
| `Decay.OnTurnEnd` | 挂在 GE **Asset Tag**；回合末 `GA_StatusTurnHandler` 衰减 |
| `Artifact` / `Barricade` | v0.2+ 扩展 Buff |

### STS.Phase.* vs STS.Event.*

| 类型 | 区别 |
|------|------|
| **Phase** | 挂在 ASC 上的**状态**；`GA_PlayCard` 的 `ActivationBlockedTags` |
| **Event** | **一次性广播**；`ASC->HandleGameplayEvent`；遗物/Buff 监听 |

### STS.Relic.Trigger.* vs STS.Event.*

遗物 DataAsset 配置 **Trigger**；战斗逻辑在对应时机发 **Event**。二者名称对应，便于策划理解：

| Relic.Trigger | 对应 Event |
|---------------|------------|
| `CombatStart` | `Event.Combat.Start` |
| `CombatVictory` | `Event.Combat.Victory` |
| `PlayerTurnStart` | `Event.Turn.PlayerStart` |
| `PlayerTurnEnd` | `Event.Turn.PlayerEnd` |
| `OnCardPlayed` | `Event.Card.Played` |

### STS.Action.*

`USTSAbilitySet` 里每条 GA 的 **ActionTag**，供 `USTSAbilitySystemComponent::TryActivateAbilityByActionTag` 查找 Spec。

### STS.Data.*

`UGameplayEffect` 的 **SetByCaller** 键：`GE_Damage` 读 `Data.Damage`，`GE_EnergyCost` 读 `Data.Cost`。

### STS.Granted.Power

能力牌打出后授予 `STS.Granted.Power.{CardName}`（运行时子 Tag）；`GA_PlayCard::CanActivate` 检查父 Tag `STS.Granted.Power` 或精确子 Tag。

### STS.UI.Layer.*

CommonUI `PushWidget` 时指定层，见 [plan/02_ui_framework.md](../plan/02_ui_framework.md)。

---

## C++ 使用示例

```cpp
#include "Core/STSGameplayTags.h"

// 门控
if (ASC->HasMatchingGameplayTag(STSGameplayTags::Phase_PlayerTurn)) { ... }

// 广播事件
FGameplayEventData Payload;
ASC->HandleGameplayEvent(STSGameplayTags::Event_Turn_PlayerStart, &Payload);

// SetByCaller
Spec.Data.SetSetByCallerMagnitude(STSGameplayTags::Data_Damage, 6.f);
```

## DataAsset 编辑器

`USTSCardData` 字段已限制 Tag 类别，例如：

- `CardTypeTag` → `meta=(Categories="STS.Card.Type")`
- `USTSRelicData.TriggerTag` → `meta=(Categories="STS.Relic.Trigger")`

在编辑器 **Project Settings → Gameplay Tags** 可查看完整树形列表。

---

## 蓝图扩展钩子（Blueprintable / K2_* 事件）

关键 C++ 类已支持蓝图子类与 `BlueprintImplementableEvent` 钩子，便于内容迭代：

| 类 | 蓝图子类示例 | 主要 K2 钩子 |
|----|--------------|--------------|
| `ASTSCombatGameState` | `BP_CombatGameState` | `K2_OnCombatInitialized`, `K2_OnPhaseChanged`, `K2_OnCardPlayed` |
| `ASTSCombatGameMode` | `BP_CombatGameMode` | `K2_OnCombatStarted` |
| `ASTSMapGameMode` | `BP_MapGameMode` | `K2_OnMapStarted` |
| `USTSRunSubsystem` | `BP_RunSubsystem`（Project Settings 指定） | `K2_OnNewRunStarted`, `K2_OnNodeEntered` |
| `USTSGameplayAbility_PlayCard` | `GA_PlayCard_BP` | `K2_ExecuteCardEffects`, `K2_CanPlayCard` |
| `USTSEffectExecutor` | `BP_EffectExecutor` | 覆写 `ExecuteEffect` |
| `USTSCardCondition` | `BP_CardCondition_*` | `CanPlayCard` |

核心流程方法（`InitCombat`、`TryPlayCard`、`NewRun` 等）使用 **BlueprintNativeEvent**，可在 BP 中 **Override** C++ 默认实现。
