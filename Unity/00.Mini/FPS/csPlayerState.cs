using UnityEngine;
using System.Collections;

public class csPlayerState : MonoBehaviour {

	private int hp = 5;
	public bool isDead = false;

	csCameraShake cameraShake = null;

	void Start(){
		cameraShake = GetComponentInChildren<csCameraShake> ();
	}


	void OnGUI(){
		float x = Screen.width / 2.0f - 100;
		Rect rect = new Rect (x, 10, 200, 25);
		if (isDead == false) {
			GUI.Box (rect, "My Health : " + hp);

			int myScore = csScoreManager.Instance ().myScore;
			int bestScore = csScoreManager.Instance ().bestScore;

			rect.y += 30;
			rect.height = 40;

			GUI.Box (rect, "Score : " + myScore + "\n" + "Best Score : " + bestScore);

		} else {
			GUI.Box (rect, "Game Over");
		}

	}


	public void DamageByEnemy(){
		if (isDead) {
			return;
		}


		--hp;
		cameraShake.PlayCameraShake ();




		if (hp <= 0) {
			isDead = true;
		}

	}



}
