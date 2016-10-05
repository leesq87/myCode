using UnityEngine;
using System.Collections;

public class csFireManager : MonoBehaviour {

	public Transform cameraTransform;
	public GameObject fireObject;
	public float power = 20.0f;

	public Transform firePoint;

	csPlayerState playerHealth = null;


	void Start(){
		playerHealth = GetComponent<csPlayerState> ();
	}

	void Update(){
		if (csPauseScript.gamePause == true)
			return;
		

		if (playerHealth.isDead) {
			return;
		}


		if(Input.GetButtonDown("Fire1")){
			GameObject obj = Instantiate(fireObject) as GameObject;
			float y = cameraTransform.transform.rotation.eulerAngles.y;

//			Vector3 ang = cameraTransform.transform.rotation.

			obj.transform.rotation = Quaternion.Euler (90,y,0);

			obj.transform.position = firePoint.transform.position;
			obj.GetComponent<Rigidbody>().velocity = cameraTransform.forward*power;
		}
	}



}
