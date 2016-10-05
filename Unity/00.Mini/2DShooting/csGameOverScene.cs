using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class csGameOverScene : MonoBehaviour {

	public GameObject gameOverText;

	void Start(){
		//StartCoroutine (gameOver());
	}
	/*
	IEnumerator gameOver(){
		while (true) {
			gameOverText.SetActive (true);

			yield return new WaitForSeconds (0.5f);

			gameOverText.SetActive (false);
			yield return new WaitForSeconds (0.5f);

		}
	}
*/
	public void sceneTrans(){
		Debug.Log ("click");
		SceneManager.LoadScene ("Game");
	}


}
