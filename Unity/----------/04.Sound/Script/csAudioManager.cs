using UnityEngine;
using System.Collections;

public class csAudioManager : MonoBehaviour {

	public AudioClip clip;

	void OnCollisionEnter(Collision collision){
		AudioManager.Instance ().PlaySfx (clip);

		Destroy (this.gameObject);
	}


}
