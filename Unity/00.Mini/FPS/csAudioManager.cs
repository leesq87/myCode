using UnityEngine;
using System.Collections;

public class csAudioManager : MonoBehaviour {

	static csAudioManager _instance = null;
	public static csAudioManager Instance(){
		return _instance;
	}

	public AudioClip music = null;

	void Start(){
		if (_instance == null)
			_instance = this;

		if(music !=null){
			GetComponent<AudioSource>().clip = music;
			GetComponent<AudioSource> ().loop = true;
			GetComponent<AudioSource>().Play();
		}
	}


	public void PlaySfx(AudioClip clip){
		GetComponent<AudioSource> ().PlayOneShot (clip);
	}



}
