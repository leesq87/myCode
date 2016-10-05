using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;


public class StartScript : MonoBehaviour {

    void Update()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            //SceneManager.LoadScene("Main");
            SoundManager.Instance().nextSceneName = "main";
            Time.timeScale = 1f;
            SceneManager.LoadScene("loadingMain");
        }

        if (Input.touchCount >= 1)
        {
            //SceneManager.LoadScene("Main");
            SoundManager.Instance().nextSceneName = "main";
            Time.timeScale = 1f;
            SceneManager.LoadScene("loadingMain");
        }
    }


}
