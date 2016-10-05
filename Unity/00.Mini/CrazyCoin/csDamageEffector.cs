using UnityEngine;
using System.Collections;

public class csDamageEffector : MonoBehaviour {

	private bool effectFlag = false;
	private Color originalColor;

	void Start(){
		originalColor = GetComponent<Renderer> ().material.color;

	}

	void Update(){
		if (effectFlag) {
			float level = Mathf.Abs (Mathf.Sin (40.0f * Time.time));

			GetComponent<Renderer> ().material.color = Color.red * level;
		}
	}

	IEnumerator ApplyDamage(int amount){
		effectFlag = true;
		yield return new WaitForSeconds (0.3f);

		effectFlag = false;
		GetComponent<Renderer> ().material.color = originalColor;
	}




}
