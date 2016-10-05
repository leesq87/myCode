using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.Collections.Generic;

public class Loading : MonoBehaviour {

    public List<Sprite> randomImg;
    public Text progressLabel;
    public Image background;

    // Use this for initialization
	void Start () {
        background.GetComponent<Image>().sprite = randomImg[Random.Range(1, 4)];
        StartCoroutine(Load());
	}
	
    IEnumerator Load()
    {
        AsyncOperation async = SceneManager.LoadSceneAsync(SoundManager.Instance().nextSceneName);
        
        while (!async.isDone)
        {
            float progress = async.progress * 100.0f;
            int pRounded = Mathf.RoundToInt(progress);

            progressLabel.text = "loading..." + pRounded.ToString() + "%";

            yield return true;
        }
    }

}
