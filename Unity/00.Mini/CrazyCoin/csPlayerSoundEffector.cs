using UnityEngine;
using System.Collections;

public class csPlayerSoundEffector : MonoBehaviour {

	public AudioClip coinSE;
	public AudioClip damageSE;

	void CatchCoin(int amount){
		GetComponent<AudioSource> ().PlayOneShot (coinSE);
	}

	void ApplyDamage(int amount){
		GetComponent<AudioSource> ().PlayOneShot (damageSE);
	}


}
