# unrealSTS 设计计划

本目录仅存放 **实施方案、Phase 任务、架构与 UI 设计**，与 Cursor 会话中的计划保持同步。

**概念学习与引擎特性说明** 见 [`DOC/`](../DOC/) 目录。

## 文档索引

| 文档 | 说明 | 状态 |
|------|------|------|
| [01_sts_gas_architecture.md](01_sts_gas_architecture.md) | 杀戮尖塔 × GAS 总体架构：插件结构、GameplayTag、卡牌/遗物/Buff、角色、Phase 0–4 | Phase 0 已落地 |
| [02_ui_framework.md](02_ui_framework.md) | CommonUI 分层 UI、WidgetController、拖动出牌 | 待实施 |

## 工程路径

- UE 工程：`unrealSTS/unrealSTS.uproject`（UE 5.7）
- 框架插件：`unrealSTS/Plugins/STSFramework`
- 内容资产：`unrealSTS/Content/STS`

## 设计原则

**学习优先：** 场景与生命周期优先映射到 UE 原生类。概念入门读 [DOC/ue_concepts_for_sts.md](../DOC/ue_concepts_for_sts.md)；实现细节见架构文档 **§0**。

## 实施顺序建议

1. **Phase 0**（已完成）— STSFramework 插件、Tag、AbilitySet
2. **Phase 1** — 基类骨架已落地；下一步：AttributeSet 逻辑、`ASTSCombatGameState` 回合机、EffectExecutor、GE 模板
3. **UI-Phase 0/1** — CommonUI 根布局 + 拖动出牌战斗 HUD
4. **Phase 2+** — 首场战斗、地图、单局循环

## 更新说明

计划文档由开发过程中迭代产生；若在 Cursor 中更新了 `.cursor/plans/` 下的计划，请同步复制到本目录。学习类文档写入 `DOC/`，不要放在 `plan/`。
