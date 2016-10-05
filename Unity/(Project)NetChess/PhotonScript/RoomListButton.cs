using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class RoomListButton : MonoBehaviour {

    public Text playerState;
    public Text roomState;

    private MainPhotonInit myManager;

    static bool canUse;

    void Start()
    {
        myManager = GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>();
        canUse = true;
    }

    public void CheckUse()
    {
        canUse = false;
    }

    public void btnJoinRoom()
    {
        if (!canUse)
        {
            return;
        }
        canUse = true;
        myManager.JoinRoom(playerState.text);

    }
    

}
