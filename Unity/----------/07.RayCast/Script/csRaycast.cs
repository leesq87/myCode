using UnityEngine;
using System.Collections;

public class csRaycast : MonoBehaviour {

	private float speed = 5.0f;

	void Update(){
		float amtMove = speed * Time.deltaTime;
		float hor = Input.GetAxis ("Horizontal");
		transform.Translate(Vector3.right*hor*amtMove);


		Debug.DrawRay (transform.position, transform.forward * 8, Color.red);

		//Raycast
		RaycastHit hit;
		if(Physics.Raycast(transform.position,transform.forward,out hit, 8)){
			Debug.Log(hit.collider.gameObject.name);
		}
	}


}
