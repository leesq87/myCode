using UnityEngine;
using System.Collections;

public class csBackScroll : MonoBehaviour {

	public float scrollSpeed = 0.5f;
	Material myMaterial;

	void Start(){
		myMaterial = GetComponent<Renderer> ().material;
	}

	void Update(){
		float newOffsetY = myMaterial.mainTextureOffset.y + scrollSpeed * Time.deltaTime;
		Vector2 newOffset = new Vector2 (0, newOffsetY);
		myMaterial.mainTextureOffset = newOffset;
	}




}
