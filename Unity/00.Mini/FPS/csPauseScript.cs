using UnityEngine;
using System.Collections;

public class csPauseScript : MonoBehaviour {

	public static bool gamePause = false;
	public Texture2D pauseButtonImage;
	public Texture2D pauseTextImage;

	void OnGUI(){
		PauseStateProcess ();
		DrawPauseText ();

	}

	void PauseStateProcess(){
		int width = pauseButtonImage.width;
		int height = pauseButtonImage.height;

		if (GUI.Button (new Rect (Screen.width - 74.0f, 10, width, height), pauseButtonImage, GUIStyle.none)) {
			gamePause = !gamePause;
			if (gamePause == true) {
				Time.timeScale = 0.0f;
			} else { 
				Time.timeScale = 1.0f;
			}
		}
	}

	void DrawPauseText(){
		if (gamePause) {
			int width = pauseTextImage.width;
			int height = pauseTextImage.height;

			float x = (Screen.width - width) / 2.0f;
			float y = (Screen.height - height) / 2.0f;

			Rect textRect = new Rect (x, y, width, height);

			GUI.DrawTexture (textRect, pauseTextImage);
		}
	}

}
