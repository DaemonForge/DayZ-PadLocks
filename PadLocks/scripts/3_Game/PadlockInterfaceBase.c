class PadlockInterfaceBase extends UIScriptedMenu
{
	protected autoptr TIntArray 		m_Combination = {0,0,0,0,0,0};
	protected autoptr TStringArray		m_LastValues = {"0","0","0","0","0","0"};
	protected static string 			m_LayoutPath4 = "Padlocks/gui/layout/LocksGUI.layout";
	protected static string 			m_LayoutPath6 = "Padlocks/gui/layout/LocksGUI_6.layout";
	protected static string 			UNLOCKIMAGE_4 = "PadLocks/gui/images/HD_Padlock_UI_UnLock.edds";
	protected static string 			SETIMAGE_4 = "PadLocks/gui/images/HD_Padlock_UI_Lock.edds";
	protected static string 			UNLOCKIMAGE_6 = "PadLocks/gui/images/Padlock_UI_Unlock_6.edds";
	protected static string 			SETIMAGE_6 = "PadLocks/gui/images/Padlock_UI_Lock_6.edds";
	protected string 					UNLOCKIMAGE;
	protected string 					SETIMAGE;
	protected bool						m_Is6Digit;
		
	
	protected ImageWidget 				m_RootImage;
	protected ButtonWidget 				m_Unlock;
	protected ButtonWidget 				m_Reset;
	protected TextWidget 				m_Unlock_Hover;
	protected TextWidget 				m_Reset_Hover;
	
	protected ImageWidget 				m_UnlockLabel; 
	
	protected EditBoxWidget 			m_Diget0;
	protected EditBoxWidget 			m_Diget1;
	protected EditBoxWidget 			m_Diget2;
	protected EditBoxWidget 			m_Diget3;
	protected EditBoxWidget 			m_Diget4;
	protected EditBoxWidget 			m_Diget5;
	
	protected ButtonWidget 				m_Diget0Up;
	protected ButtonWidget 				m_Diget1Up;
	protected ButtonWidget 				m_Diget2Up;
	protected ButtonWidget 				m_Diget3Up;
	protected ButtonWidget 				m_Diget4Up;
	protected ButtonWidget 				m_Diget5Up;
	protected ButtonWidget 				m_Diget0Down;
	protected ButtonWidget 				m_Diget1Down;
	protected ButtonWidget 				m_Diget2Down;
	protected ButtonWidget 				m_Diget3Down;
	protected ButtonWidget 				m_Diget4Down;
	protected ButtonWidget 				m_Diget5Down;
	
	override Widget Init()
    {
		m_Is6Digit = PadlockConfig.Is6DigitEnabled();
		string layoutPath;
		if (m_Is6Digit){
			layoutPath = m_LayoutPath6;
			UNLOCKIMAGE = UNLOCKIMAGE_6;
			SETIMAGE = SETIMAGE_6;
		} else {
			layoutPath = m_LayoutPath4;
			UNLOCKIMAGE = UNLOCKIMAGE_4;
			SETIMAGE = SETIMAGE_4;
		}
		
		layoutRoot 				= Widget.Cast(GetGame().GetWorkspace().CreateWidgets(layoutPath));
		m_RootImage				= ImageWidget.Cast(layoutRoot);
		
		m_Unlock 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("Unlock"));
		m_UnlockLabel			= ImageWidget.Cast(layoutRoot.FindAnyWidget("Unlock_Label"));
		m_Unlock_Hover 			= TextWidget.Cast(layoutRoot.FindAnyWidget("Unlock_Hover"));
		m_UnlockLabel.LoadImageFile(0,UNLOCKIMAGE);
		
		m_Reset 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("Reset"));
		m_Reset_Hover 			= TextWidget.Cast(layoutRoot.FindAnyWidget("Reset_Hover"));
		
		m_Diget0Up 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp0"));
		m_Diget1Up 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp1"));
		m_Diget2Up 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp2"));
		m_Diget3Up 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp3"));
		
		m_Diget0Down 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown0"));
		m_Diget1Down 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown1"));
		m_Diget2Down 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown2"));
		m_Diget3Down 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown3"));		
		
		m_Diget0				= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget0"));	
		m_Diget1				= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget1"));	
		m_Diget2				= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget2"));	
		m_Diget3				= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget3"));
		
		if (m_Is6Digit){
			m_Diget4Up 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp4"));
			m_Diget5Up 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialUp5"));
			m_Diget4Down 		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown4"));
			m_Diget5Down 		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("DialDown5"));
			m_Diget4			= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget4"));
			m_Diget5			= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Diget5"));
		}
		
		RALockControls();
		 
		return layoutRoot;
	}
	
	void ~PadlockInterfaceBase(){
		RAUnLockControls();
	}
	
	void SetPadLock(EntityAI lock){
		
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		ResetBlanks();
		if (w == m_Diget0Up){
			StepNumber(0, 1);
			return true; 
		}
		if (w == m_Diget1Up){
			StepNumber(1, 1);
			return true;
		}
		if (w == m_Diget2Up){
			StepNumber(2, 1);
			return true;
		}
		if (w == m_Diget3Up){
			StepNumber(3, 1);
			return true;
		}
		if (m_Is6Digit && w == m_Diget4Up){
			StepNumber(4, 1);
			return true;
		}
		if (m_Is6Digit && w == m_Diget5Up){
			StepNumber(5, 1);
			return true;
		}
		if (w == m_Diget0Down){
			StepNumber(0, -1);
			return true;
		}
		if (w == m_Diget1Down){
			StepNumber(1, -1);
			return true;
		}
		if (w == m_Diget2Down){
			StepNumber(2,- 1);
			return true;
		}
		if (w == m_Diget3Down){
			StepNumber(3, -1);
			return true;
		}
		if (m_Is6Digit && w == m_Diget4Down){
			StepNumber(4, -1);
			return true;
		}
		if (m_Is6Digit && w == m_Diget5Down){
			StepNumber(5, -1);
			return true;
		}
		if (w == m_Diget0){
			m_Diget0.SetText("");
			return true;
		}
		if (w == m_Diget1){
			m_Diget1.SetText("");
			return true;
		}
		if (w == m_Diget2){
			m_Diget2.SetText("");
			return true;
		}
		if (w == m_Diget3){
			m_Diget3.SetText("");
			return true;
		}
		if (m_Is6Digit && w == m_Diget4){
			m_Diget4.SetText("");
			return true;
		}
		if (m_Is6Digit && w == m_Diget5){
			m_Diget5.SetText("");
			return true;
		}
		if (w == m_Unlock){
			Unlock();
			return true;
		}
		if (w == m_Reset){
			ResetPin();
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	protected void Unlock(){
	
	}
	
	protected void ResetPin(){
	
	}
	
	protected void RefreshButtons(string image = ""){
		if (image == ""){
			image = UNLOCKIMAGE;
		}
		ResetBlanks();
		m_RootImage.LoadImageFile(0,image);
	}
	
	protected string GetUnlockText(){
		return "#unlock";
	}
	
	protected void ResetBlanks(){
		if (m_Diget0.GetText() == ""){
			m_Diget0.SetText("0");
		}
		if (m_Diget1.GetText() == ""){
			m_Diget1.SetText("0");
		}
		if (m_Diget2.GetText() == ""){
			m_Diget2.SetText("0");
		}
		if (m_Diget3.GetText() == ""){
			m_Diget3.SetText("0");
		}
		if (m_Is6Digit){
			if (m_Diget4.GetText() == ""){
				m_Diget4.SetText("0");
			}
			if (m_Diget5.GetText() == ""){
				m_Diget5.SetText("0");
			}
		}
	}
	
	protected void StepNumber(int index, int amount = 1){
		m_Combination[index] = m_Combination[index] + amount;
		if (m_Combination[index] < 0){
			m_Combination[index] = 9;
		}
		if (m_Combination[index] > 9){
			m_Combination[index] = 0;
		}
		switch (index) {
			case 0:
				m_Diget0.SetText(m_Combination[index].ToString());
			break;
			case 1:
				m_Diget1.SetText(m_Combination[index].ToString());
			break;
			case 2:
				m_Diget2.SetText(m_Combination[index].ToString());
			break;
			case 3:
				m_Diget3.SetText(m_Combination[index].ToString());
			break;
			case 4:
				if (m_Is6Digit) m_Diget4.SetText(m_Combination[index].ToString());
			break;
			case 5:
				if (m_Is6Digit) m_Diget5.SetText(m_Combination[index].ToString());
			break;
		}
		m_LastValues[index] = m_Combination[index].ToString();
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (w == m_Unlock){
			m_Unlock_Hover.SetText(GetUnlockText());
			m_Unlock_Hover.Show(true);
		}
		if (w == m_Reset){
			m_Reset_Hover.Show(true);
		}
		return super.OnMouseEnter(w,x,y);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (w == m_Unlock){
			m_Unlock_Hover.Show(false);
		}
		if (w == m_Reset){
			m_Reset_Hover.Show(false);
		}
		
		return super.OnMouseLeave(w,enterW, x, y);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished) {
		
		if (w == m_Diget0 || w == m_Diget1 || w == m_Diget2 || w == m_Diget3 || (m_Is6Digit && (w == m_Diget4 || w == m_Diget5))){
		int idx = 0;
			EditBoxWidget textB = EditBoxWidget.Cast(w);
			string d0 = textB.GetText();
			if (d0.Length() > 0){
				int lastidx = d0.Length() - 1;
				string first = d0.Substring(0,1);
				string last = d0.Substring(lastidx,1);
				switch (w) {
					case m_Diget0:
						idx = 0;
					break;
					case m_Diget1:
						idx = 1;
					break;
					case m_Diget2:
						idx = 2;
					break;
					case m_Diget3:
						idx = 3;
					break;
					case m_Diget4:
						idx = 4;
					break;
					case m_Diget5:
						idx = 5;
					break;
				}
				if (first == m_LastValues[idx]){
					d0 = last;
				} else {
					d0 = first;
				}
				if (ValidInput(d0)){
					textB.SetText(d0);
					m_LastValues[idx] = d0;
					m_Combination[idx] = d0.ToInt();
					switch (w) {
						case m_Diget0:
							SetFocus(m_Diget1);
						break;
						case m_Diget1:
							SetFocus(m_Diget2);
						break;
						case m_Diget2:
							SetFocus(m_Diget3);
						break;
						case m_Diget3:
							if (m_Is6Digit) SetFocus(m_Diget4);
						break;
						case m_Diget4:
							if (m_Is6Digit) SetFocus(m_Diget5);
						break;
					}
				} else {
					textB.SetText(m_LastValues[idx]);
				}
			} else {
				textB.SetText("0");
			}
			return true;
		}
		return super.OnChange( w, x, y, finished );
	}
	
	static const string ALLOWED_CHARACTERS = "0123456789";
	
	protected bool ValidInput(string input) {
		if (ALLOWED_CHARACTERS.Contains(input)){
			return true;
		}
		return false;
    }
	
	override void Update( float timeslice )
	{
		super.Update( timeslice );
		if( GetGame().GetInput().LocalPress( "UAUIBack", false ) )
		{
			GetGame().GetUIManager().CloseMenu(PADLOCK_INTERFACE);
		}		
	}
	
	protected void RALockControls() {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    protected void RAUnLockControls() {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }
}