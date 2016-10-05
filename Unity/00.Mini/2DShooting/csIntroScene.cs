using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class csIntroScene : MonoBehaviour {

	public GameObject IntroText;

	void Start(){
		StartCoroutine (gameStart());

	}



	void Update(){
		if (Input.GetButtonDown ("Jump")) {
			SceneTrans ();
		}

	}

	IEnumerator gameStart(){
		while (true) {
			IntroText.SetActive (true);

			yield return new WaitForSeconds (0.5f);

			IntroText.SetActive (false);
			yield return new WaitForSeconds (0.5f);

		}
	}


	public void SceneTrans(){
		SceneManager.LoadScene ("Game");
	}

}
