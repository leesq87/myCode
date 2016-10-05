using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

public class LobbyUIManager : MonoBehaviour {

    public Transform RoomViewport;
    public Transform PlayerViewport;
    public GameObject QuitGame;
    Image QuitGameBackground;

    bool openWindow = false;

    void Update()
    {
        if(Input.GetButtonDown("Cancel"))
        {
            if (openWindow == false)
            {
                BtnQuitWindowOpen();
            }
            else
            {
                BtnQuitWindowClose();
            }
        }
    }

    public void getUserList()
    {
        Debug.Log(PhotonNetwork.playerList);
        Debug.Log(PhotonNetwork.playerList.Length);
    }

    public void makeRoom()
    {
        GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>().MakeRoom();
    }

    public void BtnQuit()
    {
        Application.Quit();
    }

    public void BtnQuitWindowOpen()
    {
        QuitGameBackground = GameObject.Find("Quit").GetComponent<Image>();
        QuitGameBackground.enabled = true;
        StartCoroutine(OpenWindow(QuitGame));
    }

    public void BtnQuitWindowClose()
    {
        QuitGameBackground.enabled = false;
        StartCoroutine(CloseWindow(QuitGame));
    }

    IEnumerator OpenWindow(GameObject window)
    {
        openWindow = true;

        Vector3 windowScale = window.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            windowScale.y += 0.1f;
            window.transform.localScale = windowScale;
            yield return new WaitForEndOfFrame();
        }
        windowScale.y = 1.0f;
        window.transform.localScale = windowScale;

    }

    IEnumerator CloseWindow(GameObject window)
    {
        Vector3 windowScale = window.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            windowScale.y -= 0.1f;
            window.transform.localScale = windowScale;
            yield return new WaitForEndOfFrame();
        }

        windowScale.y = 0.0f;
        window.transform.localScale = windowScale;

        openWindow = false;
    }
}
