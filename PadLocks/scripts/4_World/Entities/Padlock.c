class Padlock extends ItemBase {
	
	autoptr PadlockInterface m_PadlockInterface;
	
	autoptr TStringArray m_RemeberedPlayers;
	int m_Combination = -1;
	int m_LastAtemptTime = 0;
	protected LockAction m_LockActionPerformed 		= LockAction.NONE;
	protected EffectSound m_Sound;
	
	const string SOUND_LOCK_OPEN 			= "combinationlock_open_SoundSet";
	const string SOUND_LOCK_CLOSE 			= "combinationlock_close_SoundSet";
	
	void Padlock() {
		RegisterNetSyncVariableInt( "m_LockActionPerformed", 0, LockAction.COUNT );
	}
	
	void SetInterface(PadlockInterface interface){
		m_PadlockInterface = interface;
	}
	
	void ClearInterface(){
		m_PadlockInterface = NULL;
	}
	
	bool CheckComboClient(){
		
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//write data
		ctx.Write( m_Combination );
		ctx.Write( m_RemeberedPlayers );
	}
	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		if ( !ctx.Read( m_Combination ) ) {
			m_Combination = -1;
			return false;
		}
		
		if ( !ctx.Read( m_RemeberedPlayers ) ) {
			m_RemeberedPlayers = new TStringArray;
			return false;
		}
		return true;
	}
	
	bool IsLocked(){
		return (m_Combination > -1);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();		
		
		//Check combination lock
		if ( GetGame().IsServer() )
		{
			EntityAI parent = GetHierarchyParent();
			if ( parent && parent.IsInherited( BaseBuildingBase ) )
			{
				LockServer( parent, true );
			}
		}		
		
		//synchronize
		Synchronize();
	}
	
	
	// --- SYNCHRONIZATION
	void Synchronize()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
			
			//UpdateVisuals();
		}
	}
	
	
	void UpdateSound()
	{
		//was locked
		if ( m_LockActionPerformed == LockAction.LOCKED )
		{
			SoundLockClose();
		}
		
		//was unlocked
		if ( m_LockActionPerformed == LockAction.UNLOCKED )
		{
			SoundLockOpen();
		}
	}
	bool IsLockAttached()
	{
		Fence fence = Fence.Cast( GetHierarchyParent() );
		if ( fence )
		{
			return true;
		}
		
		return false;
	}
	
	
	void LockServer( EntityAI parent, bool ignore_combination = false )
	{
		if ( IsLockAttached() )
		{
			if ( !ignore_combination )
			{			
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );		
				parent.GetInventory().SetSlotLock( inventory_location.GetSlot(), true );
			
				m_LockActionPerformed = LockAction.LOCKED;
			}
			SetTakeable(false);
			Synchronize();
		}
		
	}
	
	void UnlockServer( EntityAI player, EntityAI parent )
	{
		if ( IsLockAttached() )
		{
			Fence fence = Fence.Cast( parent );
			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );			
			fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );			
	
			if (player)
				player.ServerDropEntity( this );
			else
				parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
			SetPosition( fence.GetKitSpawnPosition() );
			PlaceOnSurface();
			
			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			//synchronize
			Synchronize();
		}
	}
		
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundLockOpen()
	{
		PlaySoundSet( m_Sound, SOUND_LOCK_OPEN, 0, 0 );
	}

	protected void SoundLockClose()
	{
		PlaySoundSet( m_Sound, SOUND_LOCK_CLOSE, 0, 0 );
	}
	
	
	
	bool CanUnlock(PlayerBase player){
		if (!m_RemeberedPlayers || !player || player.GetIdentity()) {return false;}
		return (m_RemeberedPlayers.Find(player.GetIdentity().GetId()) != -1);
	}
	
	protected void AddRemeberedPlayer(PlayerBase player){
		if (!player || player.GetIdentity()) { return; }
		if (!m_RemeberedPlayers) { m_RemeberedPlayers = new TStringArray; }
		if ( m_RemeberedPlayers.Find(player.GetIdentity().GetId()) == -1 ){
			m_RemeberedPlayers.Insert(player.GetIdentity().GetId());
		}
	}
}