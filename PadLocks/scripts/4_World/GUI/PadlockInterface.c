class PadlockInterface extends PadlockInterfaceBase
{
	protected Padlock 					m_Padlock;
	
	
	void ~PadlockInterface(){
		if (m_Padlock){
			m_Padlock.ClearInterface();
		}
	}
	
	override protected void Unlock(){
		int pin = m_Combination[0] * 1000;
		pin = pin + (m_Combination[1] * 100);
		pin = pin + (m_Combination[2] * 10);
		pin = pin + m_Combination[3];
		if (m_Padlock ){
			m_Padlock.RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(pin), true);
		}
	}
	
	override protected void ResetPin(){
		int pin = m_Combination[0] * 1000;
		pin = pin + (m_Combination[1] * 100);
		pin = pin + (m_Combination[2] * 10);
		pin = pin + m_Combination[3];
		if (m_Padlock ){
			m_Padlock.RPCSingleParam(PADLOCK_RESETREQUEST, new Param1<int>(pin), true);
		}
		
	}
	
	override protected string GetUnlockText(){
		if (m_Padlock && m_Padlock.HasCombination()){
			return "#unlock";
		} 
		return "#STR_PADLOCKS_SET_PIN";
	}
	
	override void SetPadLock(EntityAI lock){
		m_Padlock = Padlock.Cast(lock);
		m_Padlock.SetInterface(this);
		RefreshVisuals();
		
		SetFocus(m_Diget0);
	}
	
	
	void OnSuccess(){
	}
	
	void OnInvalidPin(){
		NotificationSystem.CreateNotification(new StringLocaliser("#STR_PADLOCKS_MOD_NAME"), new StringLocaliser("#STR_PADLOCKS_INVALID_PIN"), PADLOCK_WARNINGIMAGE, ARGB(255,255,255,255), 10);
	}
	
	void OnRateLimit(){
		NotificationSystem.CreateNotification(new StringLocaliser("#STR_PADLOCKS_MOD_NAME"), new StringLocaliser("#STR_PADLOCKS_RATE_LIMITED"), PADLOCK_WARNINGIMAGE, ARGB(255,255,255,255), 10);
	}
	
	void RefreshVisuals(){
		
		if (m_Padlock.HasCombination()){
			RefreshButtons(UNLOCKIMAGE);
			m_Reset.Show(true);
		} else {
			RefreshButtons(SETIMAGE);
			m_Reset.Show(false);
		}
	}
	
	void OnReset(){
		if (!m_Padlock){
			GetGame().GetUIManager().CloseMenu(PADLOCK_INTERFACE);
		}
		RefreshVisuals();
	}
	
}