using UnityEngine;
using System.Collections;

public class csBombProcess : MonoBehaviour {

	public GameObject groundExplosionObject;
	public GameObject airExlosionObject;

	public AudioClip clip;



	void Update(){
		float y = transform.position.y;
		if(y<0)
			Destroy(gameObject);
	}

	void OnCollisionEnter( Collision collision){
		//Debug.Log ("Collision Object Name : " + collision.gameObject.name);

		//GameObject particleObj = Instantiate (groundExplosionObject) as GameObject;
		//particleObj.transform.position = transform.position;

		csAudioManager.Instance ().PlaySfx (clip);

		int collisionLayer = collision.gameObject.layer;
		if (collisionLayer == LayerMask.NameToLayer ("ground")) {
			GameObject particleObj = Instantiate (groundExplosionObject) as GameObject;
			particleObj.transform.position = transform.position;
		} else {
			GameObject particleObj = Instantiate (airExlosionObject) as GameObject;
			particleObj.transform.position = transform.position;
		}



		Destroy (gameObject);
	}


}
