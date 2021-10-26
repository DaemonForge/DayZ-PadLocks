

class Padlock extends ItemBase {
	
	autoptr PadlockInterface m_PadlockInterface;
	
	autoptr TStringArray m_RemeberedPlayers;
	int m_Combination = -1;
	bool m_HasCombination = false;
	int m_LastAtemptTime = 0;
	protected LockAction m_LockActionPerformed 		= LockAction.NONE;
	protected EffectSound m_Sound;
	
	const string SOUND_LOCK_OPEN 			= "combinationlock_open_SoundSet";
	const string SOUND_LOCK_CLOSE 			= "combinationlock_close_SoundSet";
	
	void Padlock() {
		RegisterNetSyncVariableInt( "m_LockActionPerformed", 0, LockAction.COUNT );
		RegisterNetSyncVariableBool("m_HasCombination");
	}
	
	
	void SetInterface(PadlockInterface interface){
		m_PadlockInterface = interface;
	}
	
	void ClearInterface(){
		m_PadlockInterface = NULL;
	}
	
	void SetCombination(int pin){
		m_Combination = pin;
		if (m_Combination >= 0){
			m_HasCombination = true;
			LockServer(GetHierarchyRoot());
		} else {
			m_HasCombination = false;
		}
		SetSynchDirty();
	}
	
	override void OnStoreSave( ParamsWriteContext ctx ) {   
		super.OnStoreSave( ctx );
		
		//write data
		ctx.Write( m_Combination );
		ctx.Write( m_RemeberedPlayers );
	}
	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version ) {
		if ( !super.OnStoreLoad( ctx, version ) ){
			return false;
		}
		
		if ( !ctx.Read( m_Combination ) ) {
			m_Combination = -1;
			return false;
		}
		
		if ( !ctx.Read( m_RemeberedPlayers ) ) {
			m_RemeberedPlayers = new TStringArray;
			return false;
		}
		if (m_Combination >= 0){
			m_HasCombination = true;
		} else {
			m_HasCombination = false;
		}
		if (GetGame().IsServer()){
			SetSynchDirty();
		}
		return true;
	}
	
	bool IsLocked(){
		return (m_Combination > -1) || HasCombination();
	}
	
	override void AfterStoreLoad() {	
		super.AfterStoreLoad();		
		
		//Check combination lock
		if ( GetGame().IsServer() ) {
			EntityAI parent = GetHierarchyParent();
			if ( parent && parent.IsInherited( BaseBuildingBase ) ) {
				LockServer( parent );
			}
		}		
		
		//synchronize
		Synchronize();
		if (m_Combination >= 0){
			m_HasCombination = true;
		} else {
			m_HasCombination = false;
		}
		if (GetGame().IsServer()){
			SetSynchDirty();
		}
	}
	
	bool HasCombination(){
		return m_HasCombination;
	}
	
	// --- SYNCHRONIZATION
	void Synchronize() {
		if ( GetGame().IsServer() ) {
			SetSynchDirty();
			
			//UpdateVisuals();
		}
	}
	
	
	void UpdateSound() {
		//was locked
		if ( m_LockActionPerformed == LockAction.LOCKED ) {
			SoundLockClose();
		}
		
		//was unlocked
		if ( m_LockActionPerformed == LockAction.UNLOCKED ) {
			SoundLockOpen();
		}
	}
	
	bool IsLockAttached() {
		Fence fence = Fence.Cast( GetHierarchyParent() );
		if ( fence ) {
			return true;
		}
		
		return false;
	}
	
	
	void LockServer( EntityAI parent) {
		if ( IsLockAttached() ) {			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );		
			parent.GetInventory().SetSlotLock( inventory_location.GetSlot(), true );
			
			m_LockActionPerformed = LockAction.LOCKED;
			SetTakeable(false);
			Synchronize();
		}
		
	}
	
	void UnlockServer( EntityAI player, EntityAI parent ) {
		if ( IsLockAttached() )
		{
			ItemBase fence = ItemBase.Cast( parent );
			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );			
			fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );			
	
			if (player) {
				player.ServerDropEntity( this );
			} else {
				parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
			}
			PlaceOnSurface();
			SetCombination(-1);
			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			//synchronize
			Synchronize();
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		int pin;
		
		Param1<int> resetReq;
		if (rpc_type == PADLOCK_RESETREQUEST && GetGame().IsClient()) {
			if (ctx.Read(resetReq)) {
				
			}
		}
		if (rpc_type == PADLOCK_RESETREQUEST && GetGame().IsServer()) {
			if (ctx.Read(resetReq)) {
				pin = resetReq.param1;
				if (m_Combination != pin){
					RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.INVALIDPIN), true, sender);
				} else {
					SetCombination(-1);
					RPCSingleParam(PADLOCK_RESETREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
				}
			}
		}
		if (rpc_type == PADLOCK_OPENREQUEST && GetGame().IsClient()) {
			Param1<bool> openReq;
			if (ctx.Read(openReq)) {
				UIScriptedMenu menu = GetGame().GetUIManager().EnterScriptedMenu(PADLOCK_INTERFACE,NULL);
				Print(menu);
				PadlockInterface interface = PadlockInterface.Cast(menu);
				interface.SetPadLock(this);
				SetInterface(interface);
			}
		}
		Param1<int> UnlockReq;
		if (rpc_type == PADLOCK_UNLOCKREQUEST && GetGame().IsClient()) {
			if (ctx.Read(UnlockReq) && m_PadlockInterface) {
				if (UnlockReq.param1 == PadLockRespones.SUCCESS){
					m_PadlockInterface.OnSuccess();
					GetGame().GetUIManager().CloseMenu(PADLOCK_INTERFACE);
				}
				if (UnlockReq.param1 == PadLockRespones.INVALIDPIN){
					m_PadlockInterface.OnInvalidPin();
					
				}
				if (UnlockReq.param1 == PadLockRespones.RATELIMITED){
					m_PadlockInterface.OnRateLimit();
				}
			}
		}
		if (rpc_type == PADLOCK_UNLOCKREQUEST && GetGame().IsServer() && sender) {
			if (ctx.Read(UnlockReq)) {
				int curtime = GetGame().GetTime();
				if (curtime < m_LastAtemptTime){
					Print("[PadLock] Player " + sender.GetName() + " rate limited");
					RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.RATELIMITED), true, sender);
					return;
				}
				m_LastAtemptTime = curtime + 6000;
				pin = UnlockReq.param1;
				Print(UnlockReq.param1);
				if (!HasCombination()){
					Print("[PadLock] Player " + sender.GetName() + " set pin " + pin);
					SetCombination(pin);
					//AddRemeberedPlayer(sender);
					RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
					Fence fenceSet = Fence.Cast( GetHierarchyParent() );
					if ( fenceSet ) {
						fenceSet.OpenFence();
					} else {
						ItemBase itemSet = ItemBase.Cast(GetHierarchyParent());
						if (itemSet){
							itemSet.Open();
						}
					}
				} else if (m_Combination == pin){
					Print("[PadLock] Player " + sender.GetName() + " used pin " + pin +  " vs " + m_Combination);
					AddRemeberedPlayer(sender);
					RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
					Fence fence = Fence.Cast( GetHierarchyParent() );
					if ( fence ) {
						fence.OpenFence();
					} else {
						ItemBase itemOpn = ItemBase.Cast(GetHierarchyParent());
						if (itemOpn){
							itemOpn.Open();
						}
					}
				} else {
					Print("[PadLock] Player " + sender.GetName() + " tried invalid pin " + pin);
					RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.INVALIDPIN), true, sender);
				}
			}
		}

	}
	
	
	bool CanUnlock(PlayerIdentity player){
		if (!m_RemeberedPlayers || !player ) {return false;}
		return (m_RemeberedPlayers.Find(player.GetId()) != -1);
	}
	
	protected void AddRemeberedPlayer(PlayerIdentity player){
		if (!player) { return; }
		if (!m_RemeberedPlayers) { m_RemeberedPlayers = new TStringArray; }
		if ( m_RemeberedPlayers.Find(player.GetId()) == -1 ){
			m_RemeberedPlayers.Insert(player.GetId());
		}
	}
	
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundLockOpen() {
		PlaySoundSet( m_Sound, SOUND_LOCK_OPEN, 0, 0 );
	}

	protected void SoundLockClose() {
		PlaySoundSet( m_Sound, SOUND_LOCK_CLOSE, 0, 0 );
	}
	
	override void SetActions()
	{
		super.SetActions();
		
	}
	
}