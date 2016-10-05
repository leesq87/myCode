using UnityEngine;
using System.Collections;

public class csGenerator : MonoBehaviour {

	float intervalMin = 0.5f;
	float intervalMax  = 1.5f;
	float coinRate = 0.3f;

	public GameObject coinPrefab;
	public GameObject spikeBallPrefab;

	IEnumerator Start(){
		while (true){
			yield return new WaitForSeconds (Random.Range (intervalMin, intervalMax));

			GameObject prefab = (Random.value < coinRate) ? coinPrefab : spikeBallPrefab;

			float theta = Random.Range (0.0f, Mathf.PI * 2.0f);
			Vector3 position = new Vector3 (Mathf.Cos (theta), 0.0f, Mathf.Sin (theta)) * 5.5f;

			position.y = 2.5f;

			Instantiate(prefab,position,Quaternion.identity);
		}
	}



}
