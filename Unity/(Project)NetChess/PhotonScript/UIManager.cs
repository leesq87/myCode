using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;


public class UIManager : MonoBehaviour {

    private static UIManager _instance;

    public static UIManager Instance()
    {
        return _instance;
    }

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
    }

    public InputField txtPlayerID;
    public InputField txtPlayerPW;
    public Toggle SaveID;
    public Toggle AutoLogin;

}
