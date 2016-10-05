using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections.Generic;

public class MainPhotonInit : MonoBehaviour {


    public string GuestID;


    public Button btnRoom;
    public Transform RoomViewport;

    public Button btnPlayer;
    public Transform PlayerViewport;

    void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
        PhotonNetwork.ConnectUsingSettings("NetChess 1.0");
        Debug.Log("Awake");
    }

    public void GuestLogin()
    {
        Debug.Log("Guest");
        //if(UIManager.Instance().txtPlayerID.text == null)
        //{
        GuestID = "Guest" + Random.Range(0, 100);
        //}

        if (string.IsNullOrEmpty(PhotonNetwork.playerName))
        {
            PhotonNetwork.playerName = GuestID;
        }

        PhotonNetwork.JoinLobby();
        StartCoroutine(this.MoveToLobby());
    }

    public void FacebookLogin(string UserID) 
    {
        GuestID = UserID;

        PhotonNetwork.JoinLobby();
        StartCoroutine(this.MoveToLobby());
    }

	public void BackToLobby()
	{
		PhotonNetwork.LeaveRoom();
		StartCoroutine (ReJoinLobby ());

	}

	IEnumerator ReJoinLobby()
	{
		yield return MoveToLobby();

		yield return CheckConnect ();

		PhotonNetwork.JoinLobby ();
		OnReceivedRoomListUpdate ();

		yield return true;
	}

	IEnumerator CheckConnect()
	{
		while (true) {
			if (PhotonNetwork.connected && PhotonNetwork.Server == ServerConnection.MasterServer) {
				return true;
			} else
				yield return new WaitForSeconds (1f);
		}
	}

    IEnumerator MoveToLobby()
    {
        SceneManager.LoadScene("02_Lobby");
        yield return null;
        //Debug.Log(GuestID);
    }

    void OnJoinedLobby()
    {
        Debug.Log("joined Lobby");


        //StartCoroutine(this.CreatePlayerList());

    }

    IEnumerator CreatePlayerList()
    {
        Debug.Log("meC");
        PlayerViewport = GameObject.Find("GameManager").GetComponent<LobbyUIManager>().PlayerViewport;

        Button newButton = Instantiate(btnPlayer) as Button;

        PlayerListButton button = newButton.GetComponent<PlayerListButton>();

        newButton.transform.SetParent(PlayerViewport);

        yield return null;
    }

    void OnPhotonRandomJoinFailed()
    {
        Debug.Log("Fail Join Room");

    }

    public void CreatePlayerButton()
    {
        Debug.Log("RPC CreatePlayerButton");
        StartCoroutine(this.CreatePlayerList());
    }




    void OnCreateRoom()
    {
        Debug.Log("Create Room");


    }

    void OnJoinedRoom()
    {
        Debug.Log("Joined Room");

        PhotonNetwork.isMessageQueueRunning = false;

        StartCoroutine(this.MoveToGame());


		PhotonNetwork.isMessageQueueRunning = true;

    }

    IEnumerator MoveToGame()
    {
        SceneManager.LoadScene("03_Game");
        yield return null;
        PhotonNetwork.isMessageQueueRunning = true;
    }

    //void OnGUI()
    //{
    //    GUILayout.Label(PhotonNetwork.connectionStateDetailed.ToString());
    //}

    public void getUserList()
    {
        Debug.Log(PhotonNetwork.playerList.Length);
    }


    public void MakeRoom()
    {
        RoomOptions opt = new RoomOptions();
        opt.maxPlayers = 2;

        PhotonNetwork.playerName = GuestID;
        PhotonNetwork.CreateRoom(GuestID, opt, TypedLobby.Default);

        GameObject.Find("GameManager").GetComponent<CheckUsed>().getRoomList(GuestID);
        GameObject.Find("GameManager").GetComponent<CheckUsed>().setRoomState(GuestID);

    }
    //Room List 갱신 및 UI 스크롤뷰에 방 버튼 instantiate
    void OnReceivedRoomListUpdate()
    {
        Debug.Log("receive room list : " + PhotonNetwork.GetRoomList().Length);
        RoomViewport = GameObject.Find("GameManager").GetComponent<LobbyUIManager>().RoomViewport;

        for (int i = 0; i < RoomViewport.childCount; ++i)
        {
            Destroy(RoomViewport.GetChild(i).gameObject);
        }

        foreach (RoomInfo room in PhotonNetwork.GetRoomList())
        {
            Debug.Log(PhotonNetwork.GetRoomList());

            Button newButton = Instantiate(btnRoom) as Button;
            newButton.transform.name = room.name;

            GameObject.Find("GameManager").GetComponent<CheckUsed>().getRoomList(room.name);

            RoomListButton button = newButton.GetComponent<RoomListButton>();
            button.playerState.text = room.name;

            if (room.playerCount == 1)
            {
                if (!GameObject.Find("GameManager").GetComponent<CheckUsed>().checkUsed(room.name))
                {
                    button.roomState.text = "WAIT";
                }
                else
                {
                    button.roomState.text = "Not Enter";
                }
            }
            else if (room.playerCount == 2)
            {
                button.roomState.text = "2/2";
                button.CheckUse();
                GameObject.Find("GameManager").GetComponent<CheckUsed>().setRoomUse(room.name);
            }
            else if (room.playerCount == 0)
            {
                Destroy(newButton);
            }
            newButton.transform.SetParent(RoomViewport);
            newButton.transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
        }
    }

    public void JoinRoom(string str)
    {
        Debug.Log("Room Enter : " + str);

        if (!GameObject.Find("GameManager").GetComponent<CheckUsed>().checkUsed(str))
        {
            Debug.Log("aaa");
            PhotonNetwork.playerName = GuestID;
            PhotonNetwork.JoinRoom(str);
            return;
        }
        Debug.Log("adsf");
        return;
    }

    
}
