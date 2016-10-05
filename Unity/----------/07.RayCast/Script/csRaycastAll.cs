using UnityEngine;
using System.Collections;

public class csRaycastAll : MonoBehaviour {


	private float speed = 5.0f;

	void Update(){
		float amtMove = speed * Time.deltaTime;
		float hor = Input.GetAxis ("Horizontal");
		transform.Translate(Vector3.right*hor*amtMove);


		Debug.DrawRay (transform.position, transform.forward * 8, Color.red);

		RaycastHit[] hits;
		hits = Physics.RaycastAll (transform.position, transform.forward, 8.0f);

		for (int i = 0; i < hits.Length; i++) {
			RaycastHit hit = hits [i];
			Debug.Log (hit.collider.gameObject.name);
		}


	}


}
