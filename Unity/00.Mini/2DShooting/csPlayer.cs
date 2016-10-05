using UnityEngine;
using System.Collections;

public class csPlayer : MonoBehaviour {

	public float moveSpeed = 0.5f;

	public GameObject laserPrefab;
	public static bool canShoot = false;

	float shootDelay = 0.5f;
	float shootTimer = 0.0f;



	void Update(){
		MovePlayer ();
		ShootLaser ();
	}

	void MovePlayer(){
		float moveX = moveSpeed * Time.deltaTime * Input.GetAxis ("Horizontal");
		transform.Translate (moveX, 0, 0);


		//not mave to out of Camera view
		Vector3 viewPos = Camera.main.WorldToViewportPoint (transform.position);
		viewPos.x = Mathf.Clamp01 (viewPos.x);
		Vector3 worldPos = Camera.main.ViewportToWorldPoint (viewPos);

		transform.position = worldPos;

	}

	void ShootLaser(){
		if(canShoot == true){
			if(shootTimer >shootDelay){
				Instantiate(laserPrefab,transform.position,Quaternion.identity);
				shootTimer = 0.0f;
			}
			shootTimer += Time.deltaTime;
		}
	}




}
