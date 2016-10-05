using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class GameManager : MonoBehaviour {

	public static GameManager instance;

	int score = 0;
	public Text scoreText;
	public GameObject readyText;


	void Awake(){
		if(GameManager.instance ==null){
			GameManager.instance = this;
		}
	}

	void Start(){
		Invoke ("StartGame", 3.0f);
		readyText.SetActive (false);
		StartCoroutine (showReady ());

	}

	void StartGame ()
	{
		csPlayer.canShoot = true;
		csSpawnManager.isSpawn = true;
	}

	public void AddScore(int score){
		this.score += score;
		scoreText.text = "Score : " + this.score;
	}

	void Update(){

	}

	IEnumerator showReady(){
		int count = 0;
		while (count < 3) {
			readyText.SetActive (true);

			yield return new WaitForSeconds (0.5f);

			readyText.SetActive (false);
			yield return new WaitForSeconds (0.5f);

			count++;
		}
	}

}
