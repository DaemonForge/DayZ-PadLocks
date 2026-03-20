const float BOLTCUTTER_DAMAGE_PER_SECOND = 0.8;

class ActionCutPadlockCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousCutPadlock(PadlockConfig.GetRaidDamage(), BOLTCUTTER_DAMAGE_PER_SECOND);
	}
};

class ActionCutPadlock: ActionContinuousBase
{
	typename m_LastValidType;
	string m_CurrentDamageZone = "";
	int m_LastValidComponentIndex = -1;
	const float MAX_ACTION_DIST = 3.0;
	
	void ActionCutPadlock()
	{
		m_CallbackClass = ActionCutPadlockCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
		m_LockTargetOnUse = false;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined; //To change?
		m_ConditionTarget = new CCTNone; //CCTNonRuined( UAMaxDistances.BASEBUILDING ); ??
	}

	override string GetText()
	{
		return "#STR_PADLOCKS_CUT_PADLOCK";
	}
 
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ItemBase targetItem;
		Padlock padlock;
		if ( Class.CastTo(targetItem, target.GetObject()) || Class.CastTo(targetItem, target.GetParent())) {
			  if (Class.CastTo(padlock, targetItem.GetPadlock()) ){
					return padlock.CanBeRaidedWith(item) && PadlockConfig.CanRaid(targetItem.GetType());
			  }
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		super.OnFinishProgressServer(action_data);
	}
};