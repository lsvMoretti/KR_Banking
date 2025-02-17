class PluginKrBankingClientManager extends PluginBase
{
    protected ref KR_BankingMenu                    m_BankingMenu;
    protected int                                   m_PlayersCurrency;
    protected bool                                  m_IsFirstRequest = true;
    protected bool                                  m_IsWaitingForServersResponse;
    protected string                                m_ClanID;
    protected string                                m_PlainID;
    protected ref KR_BankingClientConfig            m_clientSettings;
    protected ref array<ref bankingplayerlistobj>   m_BankingPlayers;
    protected ref ClanDataBaseManager               m_OwnClan;
    protected bool                                  m_AdminMenuNeedsAnUpdate = false;

    void PluginKrBankingClientManager()
    {
        if(GetGame().IsClient() && !GetGame().IsServer()) //Maybe this will solve wrong rpc call.
        {
            Init();
        }
    }

    void Init()
    {
        GetRPCManager().AddRPC("KR_BANKING","PlayerDataResponse", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("KR_BANKING","ServerConfigResponse", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("KR_BANKING","PlayeristResponse", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("KR_BANKING", "ClanSyncRespose", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("KR_BANKING", "UIQuitRequest", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("KR_BANKING", "MoneyDropRecvied", this, SingleplayerExecutionType.Client);
        GetRPCManager().SendRPC("KR_BANKING", "ServerConfigRequest", null, true);
    }

    //!Gets called when client opens the Banking Menu
    void PlayerDataResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            Param3<int, string, int> data;
            if ( !ctx.Read( data ) ) return;
            m_PlayersCurrency = data.param1;
            m_ClanID          = data.param2;
            m_clientSettings.IncreaseMaxLimit(data.param3);

        }
    }

    void ServerConfigResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            Param2<ref KR_BankingClientConfig, string> data;
            if ( !ctx.Read( data ) ) return;
            m_clientSettings = new KR_BankingClientConfig(data.param1.MaxCurrency, data.param1.InteractDelay, data.param1.isRobActive, data.param1.isBankCardNeeded, data.param1.BankingCurrency, data.param1.CostsToCreateClan, data.param1.MaxClanAccountLimit, data.param1.IsClanAccountActive);
            m_PlainID = data.param2;
            m_clientSettings.TimeInSecToRobATM = data.param1.TimeInSecToRobATM;
            
        }
    }

    void PlayeristResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            Param1<ref array<ref bankingplayerlistobj>> data;
            if ( !ctx.Read( data ) ) return;
            if(m_BankingPlayers)
                m_BankingPlayers.Clear();
            m_BankingPlayers = data.param1;
            if(m_BankingMenu && !m_AdminMenuNeedsAnUpdate)
                m_BankingMenu.InvokePlayerList();
            if(m_AdminMenuNeedsAnUpdate)
                GetBankingClientAdminManager().UpdatePlayerlist();
        }
    }

    void ClanSyncRespose(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            Param1<ref ClanDataBaseManager> data;
            if (!ctx.Read(data)) return;

            m_OwnClan = data.param1;
            m_OwnClan.SetMembers(data.param1.GetClanMembers());
            if(m_BankingMenu)
                m_BankingMenu.LoadClanLogs();
        }
    }

    void UIQuitRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            if(m_BankingMenu && m_BankingMenu.IsVisible())
            {
                CloseBankingMenu();
            }
        }
    }

    void MoneyDropRecvied(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type == CallType.Client)
        {
            SEffectManager.PlaySoundOnObject( "MoneyDrop_SoundSet", GetGame().GetPlayer() );
        }
    }

    void OpenBankingMenu()
    {
        GetRPCManager().SendRPC("KR_BANKING", "PlayerDataRequest", null, true); //Send RPC for data.
        if(GetGame().GetUIManager().GetMenu() == NULL && m_BankingMenu == null)
        {
            m_BankingMenu = KR_BankingMenu.Cast(GetGame().GetUIManager().EnterScriptedMenu(KR_BANKING_MENU, null));
            m_BankingMenu.SetIsBankingMenuOpen(false);
        }
        else
        {
            if(GetGame().GetUIManager().GetMenu() == NULL && !m_BankingMenu.IsBankingMenuOpen())
            {
                GetGame().GetUIManager().ShowScriptedMenu(m_BankingMenu, NULL);
                m_BankingMenu.SetIsBankingMenuOpen(true);
            }
        }
    }

    void CloseBankingMenu()
    {
        if(m_BankingMenu && m_BankingMenu.IsVisible())
        {
            m_BankingMenu.CloseBankingMenu();
        }
    }

    void RequestOnlinePlayers(bool AdminRequest = false)
    {
        GetRPCManager().SendRPC("KR_BANKING", "PlayerListRequst", null, true);
        m_AdminMenuNeedsAnUpdate = AdminRequest;
    }

    void RequestRemoteToWithdraw(int amount, int mode)
    {
        GetRPCManager().SendRPC("KR_BANKING", "WithdrawRequest", new Param2<int, int>(amount, mode), true);
    }

    void RequestRemoteToDeposit(int amount, int mode)
    {
        GetRPCManager().SendRPC("KR_BANKING", "DepositRequest", new Param2<int, int>(amount, mode), true);
    }

    void RequestRemoteForTransfer(string targetPlainID, int amount)
    {
        GetRPCManager().SendRPC("KR_BANKING", "TransferRequest", new Param2<string, int>(targetPlainID, amount), true);
    }

    void RequestRemoteLeaveClan()
    {
        GetRPCManager().SendRPC("KR_BANKING", "ClanMemberLeave", new Param1<string>(GetSteamID()), true);
    }

    void RequestRemoteClanCreate(string Clanname, string ClanTag)
    {
        if(!Clanname || !ClanTag)
            return;
        GetRPCManager().SendRPC("KR_BANKING", "ClanCreateRequest", new Param2<string, string>(Clanname, ClanTag), true);
    }

    void RequestEditPermission(ref PermissionObject newPermission, string TargetsSteamID)
    {
        if(!newPermission || !TargetsSteamID) return;

        GetRPCManager().SendRPC("KR_BANKING", "ClanUpdateMember", new Param2<PermissionObject, string>(newPermission, TargetsSteamID), true);
    }

    void RequestRemoteEditClan(string Name, string Tag)
    {
        GetRPCManager().SendRPC("KR_BANKING", "ClanUpdate", new Param2<string, string>(Name, Tag), true);
    }

    ref ClanDataBaseManager GetClientsClanData()
    {
        return m_OwnClan;
    }

    array<ref CurrencySettings> GetServersCurrencyData()
    {
        return m_clientSettings.BankingCurrency;
    }

    ref KR_BankingClientConfig GetClientSettings()
    {
        return m_clientSettings;
    }

    int GetBankCredits()
    {
        return m_PlayersCurrency;
    }
    
    //!Returns the currency Ammount in Players Invenory
    int GetPlayerCurrencyAmount()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		int currencyAmount = 0;
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		ItemBase item;
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));

			if (!item)
				continue;

			for (int j = 0; j < GetServersCurrencyData().Count(); j++)
			{
				if(item.GetType() == GetServersCurrencyData().Get(j).CurrencyName)
				{
					currencyAmount += GetItemAmount(item) * GetServersCurrencyData().Get(j).CurrencyValue;
				}
			}
		}
		return currencyAmount;
	}

    ref array<ref bankingplayerlistobj> GetOnlinePlayers()
    {
        return m_BankingPlayers;
    }

    bool hasClan()
    {
        if(m_ClanID && m_ClanID != "NONE")
            return true;
        return false;
    }

    void RequestClanData()
    {
        GetRPCManager().SendRPC("KR_BANKING", "ClanSyncRequest", null, true);
    }

    void AddMemberToClan(string SteamID)
    {
        GetRPCManager().SendRPC("KR_BANKING", "ClanAddMember", new Param1<string>(SteamID), true);
    }

    void RemoveMember(string SteamID)
    {
        GetRPCManager().SendRPC("KR_BANKING", "ClanRemoveMember", new Param1<string>(SteamID), true);
    }

    int GetItemAmount(ItemBase item)
	{
		Magazine mgzn = Magazine.Cast(item);
				
		int itemAmount = 0;
		if( item.IsMagazine() )
		{
			itemAmount = mgzn.GetAmmoCount();
		}
		else
		{
			itemAmount = QuantityConversions.GetItemQuantity(item);
		}
		
		return itemAmount;
	}
    
    bool WaitForServerResponse()
    {
        return m_IsWaitingForServersResponse;
    }

    ref PermissionObject GetClanPermission()
    {
        if(m_OwnClan)
        {
            for(int i = 0; i < m_OwnClan.GetClanMembers().Count(); i++)
            {
                if(m_OwnClan.GetClanMembers().Get(i).GetPlainID() == GetSteamID())
                    return m_OwnClan.GetClanMembers().Get(i).GetPermission();
            }
        }

        return null;
    }
    void SendNotification(string Message, bool IsError = false)
	{
		#ifdef NOTIFICATIONS
			if(IsError)
				NotificationSystem.SimpleNoticiation(" " + Message, "Banking", "KR_Banking/data/Logos/notificationbanking.edds", ARGB(240, 255, 0, 0), 5);
			else
			NotificationSystem.SimpleNoticiation(" " + Message, "Banking", "KR_Banking/data/Logos/notificationbanking.edds", ARGB(240, 255, 13, 55), 5);
		#else
			if(IsError)
				NotificationSystem.AddNotificationExtended(5, "Banking ERROR", Message, "KR_Banking/data/Logos/notificationbanking.edds");
			else
				NotificationSystem.AddNotificationExtended(5, "Banking", Message, "KR_Banking/data/Logos/notificationbanking.edds");
		#endif
	}

    //!returns local players Steamid....
    string GetSteamID()
    {
        return m_PlainID;
    }
};

PluginKrBankingClientManager GetBankingClientManager()
{
	return PluginKrBankingClientManager.Cast(GetPluginManager().GetPluginByType(PluginKrBankingClientManager));
};