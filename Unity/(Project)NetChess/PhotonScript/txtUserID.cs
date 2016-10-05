using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class txtUserID : MonoBehaviour {

    void Start()
    {
        this.GetComponent<Text>().text = GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>().GuestID;
    }

}
