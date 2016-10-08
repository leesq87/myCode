using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class CameraAsBackground1 : MonoBehaviour {

    private RawImage image;
    private WebCamTexture cam;

    void Start() {
        image = GetComponent<RawImage>();
        cam = new WebCamTexture(Screen.width, Screen.height);
        image.texture = cam;
        cam.Play();
    }

}
