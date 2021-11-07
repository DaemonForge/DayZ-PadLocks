class CAContinuousCutPadlock : CAContinuousBase
{
	protected float 		m_LockDamagePerSecond;
	protected float 		m_ToolDamagePerSecond;
	protected float 		m_TimeElpased;
	protected float 		m_DefaultTimeStep = 0.5;
	protected float 		m_LockDamageDone;
	protected float 		m_ToolDamageDone;
	protected float 		m_TotalLockDamageDone;
	protected float 		m_TotalToolDamageDone;
	protected float 		m_TotalLockHealth;
	protected Padlock		m_Padlock;
	
	void CAContinuousCutPadlock( float lock_dmg_per_sec, float tool_dmg_per_sec )
	{
		m_LockDamagePerSecond = lock_dmg_per_sec;
		m_ToolDamagePerSecond = tool_dmg_per_sec;
	}
	

	override void Setup( ActionData action_data )
	{
		m_TimeElpased = 0;
		ItemBase target;
		
		if ((Class.CastTo(target, action_data.m_Target.GetObject()) && target.IsPadlocked()) || (Class.CastTo(target, action_data.m_Target.GetParent()) && target.IsPadlocked())){
			m_Padlock = Padlock.Cast(target.GetPadlock());
			m_Padlock.SyncHealth();
			m_TotalLockHealth = m_Padlock.GetSyncedHealth();
		}
		
		
	}
	
	override int Execute( ActionData action_data )
	{
		if ( !action_data.m_Player )
		{
			return UA_ERROR;
		}
		
		if ( action_data.m_MainItem.IsRuined() || m_Padlock.IsRuined())
		{
			return UA_FINISHED;
		}
		else
		{
			if ( m_LockDamageDone < m_TotalLockHealth )
			{
				m_LockDamageDone += m_LockDamagePerSecond * action_data.m_Player.GetDeltaT();
				m_ToolDamageDone += m_ToolDamagePerSecond * action_data.m_Player.GetDeltaT();
				m_TimeElpased += action_data.m_Player.GetDeltaT();
				
				if ( m_TimeElpased >= m_DefaultTimeStep )
				{
					HandleDamage( action_data );
					m_TimeElpased = 0;
				}
				return UA_PROCESSING;
			}
			else
			{
				HandleDamage( action_data );
				OnCompletePogress(action_data);
				return UA_FINISHED;
			}
		}
	}
	
	override int Cancel( ActionData action_data )
	{
		if ( !action_data.m_Player || !action_data.m_MainItem )
		{
			return UA_ERROR;
		}
		
		HandleDamage( action_data );
		return UA_CANCEL;
	}
	
	override int Interrupt( ActionData action_data )
	{				
		return super.Interrupt( action_data );
	}
	
	override float GetProgress()
	{	
		return m_TotalLockDamageDone/m_TotalLockHealth;
	}
	
	
	void HandleDamage( ActionData action_data )
	{
		m_TotalLockDamageDone += m_LockDamageDone;
		if ( GetGame().IsServer() )
		{
			m_Padlock.DecreaseHealth("","", m_LockDamageDone);
			action_data.m_MainItem.DecreaseHealth("","",m_ToolDamageDone);
			m_Padlock.SyncHealth();
			Print("PADLOCK HEALTH: " + m_Padlock.GetHealth("",""));
		}
		m_LockDamageDone = 0;
		m_ToolDamageDone = 0;
	}
};