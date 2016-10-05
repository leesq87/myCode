using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerListButton : MonoBehaviour {

    public Text txtPlayerID;

    private MainPhotonInit myManager;
    private PhotonView pv;

    void Start()
    {
        pv = GetComponent<PhotonView>();
        myManager = GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>();
        txtPlayerID.text = myManager.GuestID;
        //pv.RPC("callRPC", PhotonTargets.Others);
    }


    public void Button_Click()
    {
        Debug.Log("user Click");
    }

    //[PunRPC]
    //void callRPC()
    //{
    //    GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>().CreatePlayerButton();
    //}
}
