using UnityEngine;
using System.Collections;

public class csPlayerStatus : MonoBehaviour {

	private int life = 100;
	private int score = 0;

	public GameObject coinFx;
	public GameObject damageFx;
	public GameObject deathFx;
	public GUISkin skin;

	void CatchCoin(int amount){
		score += amount;

		Instantiate (coinFx, transform.position, transform.rotation);
	}

	void ApplyDamage(int amount){

		life -= amount;

		if(life <=0){
			Instantiate(deathFx,transform.position, transform.rotation);

			Destroy(transform.parent.gameObject);

			GameObject.FindWithTag("GameController").SendMessage("EndGame",score);
		} else {
			Instantiate(damageFx,transform.position,transform.rotation);
		}
	}


	void OnGUI(){
		GUI.skin = skin;

		Rect rect = new Rect (0, 0, Screen.width, Screen.height);

		GUI.Label (rect, "LIFE : " + life.ToString (), "life");

		GUI.Label (rect, "SCORE : " + score.ToString (), "score");
	}



}
