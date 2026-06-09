// Copyright unrealSTS. All Rights Reserved.

#include "Core/STSGameplayTags.h"

namespace STSGameplayTags
{
	// STS.Card.Type.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Type_Attack, "STS.Card.Type.Attack", "Attack card");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Type_Skill, "STS.Card.Type.Skill", "Skill card");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Type_Power, "STS.Card.Type.Power", "Power card");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Type_Status, "STS.Card.Type.Status", "Status card");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Type_Curse, "STS.Card.Type.Curse", "Curse card");

	// STS.Card.Rarity.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Rarity_Basic, "STS.Card.Rarity.Basic", "Basic starter card");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Rarity_Common, "STS.Card.Rarity.Common", "Common rarity");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Rarity_Uncommon, "STS.Card.Rarity.Uncommon", "Uncommon rarity");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Rarity_Rare, "STS.Card.Rarity.Rare", "Rare rarity");

	// STS.Card.Pool.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Pool_Ironclad, "STS.Card.Pool.Ironclad", "Ironclad card pool");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Pool_Colorless, "STS.Card.Pool.Colorless", "Colorless card pool");

	// STS.Card.State.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_State_Upgraded, "STS.Card.State.Upgraded", "Permanent upgrade");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_State_CombatUpgrade, "STS.Card.State.CombatUpgrade", "Combat-only upgrade");

	// STS.Card.Keyword.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_Exhaust, "STS.Card.Keyword.Exhaust", "Exhaust keyword");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_Ethereal, "STS.Card.Keyword.Ethereal", "Ethereal keyword");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_Retain, "STS.Card.Keyword.Retain", "Retain keyword");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_Unplayable, "STS.Card.Keyword.Unplayable", "Unplayable keyword");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_Innate, "STS.Card.Keyword.Innate", "Innate keyword");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Card_Keyword_XCost, "STS.Card.Keyword.XCost", "X cost keyword");

	// STS.Status.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Vulnerable, "STS.Status.Vulnerable", "Vulnerable debuff");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Weak, "STS.Status.Weak", "Weak debuff");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Poison, "STS.Status.Poison", "Poison stacks");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Strength, "STS.Status.Strength", "Strength buff");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Artifact, "STS.Status.Artifact", "Artifact buff");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Barricade, "STS.Status.Barricade", "Barricade buff");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Decay_OnTurnEnd, "STS.Status.Decay.OnTurnEnd", "Decay at turn end");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Decay_OnTurnStart, "STS.Status.Decay.OnTurnStart", "Decay at turn start");

	// STS.Phase.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Phase_PlayerTurn, "STS.Phase.PlayerTurn", "Player turn phase");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Phase_EnemyTurn, "STS.Phase.EnemyTurn", "Enemy turn phase");

	// STS.Event.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Combat_Start, "STS.Event.Combat.Start", "Combat started");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Combat_Victory, "STS.Event.Combat.Victory", "Combat victory");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Combat_Defeat, "STS.Event.Combat.Defeat", "Combat defeat");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Turn_PlayerStart, "STS.Event.Turn.PlayerStart", "Player turn started");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Turn_PlayerEnd, "STS.Event.Turn.PlayerEnd", "Player turn ended");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Turn_EnemyStart, "STS.Event.Turn.EnemyStart", "Enemy turn started");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Turn_EnemyEnd, "STS.Event.Turn.EnemyEnd", "Enemy turn ended");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Card_Played, "STS.Event.Card.Played", "Card played");

	// STS.Relic.Trigger.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_CombatStart, "STS.Relic.Trigger.CombatStart", "Relic: combat start");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_CombatVictory, "STS.Relic.Trigger.CombatVictory", "Relic: combat victory");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_PlayerTurnStart, "STS.Relic.Trigger.PlayerTurnStart", "Relic: player turn start");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_PlayerTurnEnd, "STS.Relic.Trigger.PlayerTurnEnd", "Relic: player turn end");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_OnCardPlayed, "STS.Relic.Trigger.OnCardPlayed", "Relic: on card played");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Relic_Trigger_OnDamageReceived, "STS.Relic.Trigger.OnDamageReceived", "Relic: on damage received");

	// STS.Action.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Action_PlayCard, "STS.Action.PlayCard", "Play card action");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Action_EnemyAct, "STS.Action.EnemyAct", "Enemy act action");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Action_RelicListen, "STS.Action.RelicListen", "Relic listener action");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Action_StatusTurn, "STS.Action.StatusTurn", "Status turn handler action");

	// STS.Data.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Damage, "STS.Data.Damage", "SetByCaller damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Heal, "STS.Data.Heal", "SetByCaller heal");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Block, "STS.Data.Block", "SetByCaller block");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Cost, "STS.Data.Cost", "SetByCaller energy cost");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Stacks, "STS.Data.Stacks", "SetByCaller stacks");

	// STS.Granted.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Granted_Power, "STS.Granted.Power", "Power card played parent tag");

	// STS.UI.Layer.*
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Game, "STS.UI.Layer.Game", "CommonUI game HUD layer");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_GameMenu, "STS.UI.Layer.GameMenu", "CommonUI in-game menu layer");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Menu, "STS.UI.Layer.Menu", "CommonUI fullscreen menu layer");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Modal, "STS.UI.Layer.Modal", "CommonUI modal layer");
}
