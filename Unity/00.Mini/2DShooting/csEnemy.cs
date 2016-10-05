using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;


public class csEnemy : MonoBehaviour {

	public float moveSpeed = 0.5f;
	public GameObject explosionPrefab;

	int killScore = 100;

	void Start(){
	}

	void Update(){
		MoveEnemy ();
	}

	void MoveEnemy(){
		float yMove = moveSpeed * Time.deltaTime;
		transform.Translate (0, -yMove, 0);
	}

	void OnTriggerEnter2D(Collider2D col){

		if (col.gameObject.tag == "Player") {
			Instantiate (explosionPrefab, transform.position, Quaternion.identity);

			SoundManager.instance.PlaySound ();
			Destroy (col.gameObject);
			Destroy (gameObject);
		//	StartCoroutine ("waitSec");

			endSceneTrans ();
		} else if (col.gameObject.tag == "Laser") {
			Instantiate (explosionPrefab, transform.position, Quaternion.identity);
			SoundManager.instance.PlaySound ();
			GameManager.instance.AddScore (killScore);

			Destroy (col.gameObject);
			Destroy (gameObject);
		}

		if (col.gameObject.name == "Wall2") {
			Destroy (gameObject);
		}

	}

	IEnumerator waitSec(){
		Debug.Log ("aaa");
		yield return new WaitForSeconds (0.5f);
		endSceneTrans ();
	}

	void endSceneTrans(){
		Debug.Log ("asdf");
		SceneManager.LoadScene ("End");
	}


}
