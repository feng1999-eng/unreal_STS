# unreal_STS

Unreal Engine 版杀戮尖塔（Slay the Spire）— GAS 学习项目。

## 环境

- Unreal Engine 5.7（安装路径示例：`F:\UE_5.7`）
- Visual Studio 2022（MSVC 14.38+）

## 打开工程

```
unrealSTS/unrealSTS.uproject
```

首次打开选择 **Yes** 编译。

命令行编译：

```bat
F:\UE_5.7\Engine\Build\BatchFiles\Build.bat unrealSTSEditor Win64 Development -Project="F:\unreal_STS\unrealSTS\unrealSTS.uproject"
```

## 文档

| 目录 | 用途 |
|------|------|
| [`DOC/`](DOC/) | **学习文档** — UE 概念、引擎特性与尖塔对照 |
| [`plan/`](plan/) | **计划文档** — 架构方案、Phase 任务、UI 设计 |

推荐阅读：

- [DOC/ue_concepts_for_sts.md](DOC/ue_concepts_for_sts.md) — UE 概念学习手册（World / GameInstance / GAS 等）
- [plan/01_sts_gas_architecture.md](plan/01_sts_gas_architecture.md) — GAS 架构与游戏系统设计
- [plan/02_ui_framework.md](plan/02_ui_framework.md) — CommonUI 与拖动出牌 UI 方案

## 目录结构

```
unrealSTS/
├── Plugins/STSFramework/     # GAS 框架插件（C++）
│   ├── Config/Tags/          # STSGameplayTags.ini
│   └── Source/STSFramework/
│       ├── Core/             # FSTSGameplayTags
│       └── AbilitySystem/    # USTSAbilitySet
├── Source/unrealSTS/         # 游戏模块（薄层）
└── Content/STS/              # 蓝图、DataAsset、UI、地图
```

## Phase 0 已完成

- [x] `STSFramework` 插件骨架
- [x] 启用 `GameplayAbilities` 插件
- [x] `FSTSGameplayTags` 原生 Tag 注册（`STS.*`）
- [x] `USTSAbilitySet`（Lyra 式 Give/Remove）
- [x] `Content/STS/` 资产目录树
- [x] 编译通过

## Phase 1 基类骨架（已完成，逻辑待实现）

**STSFramework 插件：**

| 领域 | 基类 |
|------|------|
| GAS | `USTSAttributeSet`、`USTSAbilitySystemComponent`、`USTSGameplayAbility`、4 个通用 GA |
| 角色 | `ASTSCombatCharacter`、`ASTSPlayerCharacter`、`ASTSEnemyCharacter`、`USTSIntentComponent` |
| 战斗 | `ASTSCombatGameState`、`USTSDamageExecution` |
| 数据 | `USTSCardData`、`USTSRelicData`、`USTSCharacterData`、`USTSEncounterData` 等 |
| Run | `USTSRunSubsystem`、`FSTSMapGraph`、`USTSMapGenerator` |

**unrealSTS 游戏模块：** `USTSGameInstance`、`ASTSPlayerController`、`ASTS*GameMode`

## 下一步（Phase 1 逻辑）

- `STSEffectExecutor` / `STSDamageExecution` 具体结算
- `ASTSCombatGameState` 回合状态机、牌堆、胜负
- GE 模板资产（Damage、Block、Status）
- 蓝图子类与首场战斗串联
