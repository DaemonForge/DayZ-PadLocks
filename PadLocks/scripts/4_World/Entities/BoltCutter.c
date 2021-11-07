class BoltCutter extends ItemBase {
	

	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCutPadlock);
	}	

}

modded class ModItemRegisterCallbacks
{

   override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior){
		super.RegisterTwoHanded(pType,pBehavior);
		pType.AddItemInHandsProfileIK("BoltCutter", "dz/anims/workspaces/player/player_main/weapons/player_main_2h_pipewrench.asi", pBehavior,			"dz/anims/anm/player/ik/two_handed/pipewrench.anm");
	}
}
