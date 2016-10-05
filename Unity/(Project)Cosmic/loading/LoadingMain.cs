using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.Collections.Generic;

public class LoadingMain : MonoBehaviour
{

    public Text progressLabel;
    public Image background;

    // Use this for initialization
    void Start()
    {
        StartCoroutine(Load());
    }

    IEnumerator Load()
    {
        AsyncOperation async = SceneManager.LoadSceneAsync("Main");

        while (!async.isDone)
        {
            float progress = async.progress * 100.0f;
            int pRounded = Mathf.RoundToInt(progress);

            progressLabel.text = "loading..." + pRounded.ToString() + "%";

            yield return true;
        }
    }

}
