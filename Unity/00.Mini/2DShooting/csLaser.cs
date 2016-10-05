using UnityEngine;
using System.Collections;

public class csLaser : MonoBehaviour {

	public float moveSpeed = 0.45f;

	void Start(){

	}

	void Update(){
		float moveY = moveSpeed * Time.deltaTime;
		transform.Translate (0, moveY, 0);

	}

	void OnTriggerEnter2D(Collider2D col){
		if(col.gameObject.tag =="Wall"){
			Destroy(gameObject);
		}
	}

	//it will change code
//	void OnBecameInvisible(){
//		Destroy (gameObject);
//	}

}
