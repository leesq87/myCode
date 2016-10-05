using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;


public class csGameOver : MonoBehaviour {

	public GUISkin skin;
	private int score;
		bool over = false;


	void EndGame(int endScore){
		score = endScore;

		over = true;
		enabled = true;
	}

	void Update(){
				if (over == true) {
						if (Input.GetButtonDown ("Jump")) {
								SceneManager.LoadScene ("Title");
						}
				}
		
	}


	void OnGUI(){
		GUI.skin = skin;
		int sw = Screen.width;
		int sh = Screen.height;

				if (over == true) {
						GUI.Label (new Rect (0, 0.2f * sh, sw, 0.3f * sh), "GAME OVER!!", "gameover");
				}
		GUI.Label (new Rect (0, 0.5f * sh, sw, 0.3f * sh), "SCORE : " + score.ToString (), "result");
	}

}

