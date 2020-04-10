﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MouseInput : MonoBehaviour
{
    [SerializeField]
    private Canvas canvas;
    [SerializeField]
    private Platform platform;
    private UIManager UIManager;
    public GameObject panel;
    enum ScaleSize
    {
        minSize,
        maxSize
    }

    private ScaleSize scale;

    private void Start()
    {
        scale = ScaleSize.minSize;
        UIManager = canvas.GetComponent<UIManager>();
        UIManager.changeScaleButton.onClick.AddListener(() => {
            switch (scale)
            {
                case ScaleSize.minSize:
                    platform.Expand();
                    scale = ScaleSize.maxSize;
                    break;
                case ScaleSize.maxSize:
                    platform.Compress();
                    scale = ScaleSize.minSize;
                    break;
            }
        });
    }

    public void Update()
    {
        Debug.Log(Input.mousePosition);
        if (Input.GetMouseButtonDown(0))
        {
            if (EventSystem.current.IsPointerOverGameObject())
                return;
            if (Input.mousePosition.x >= 0 & Input.mousePosition.x <= 1280 & Input.mousePosition.y >= 520 & Input.mousePosition.y <= 720) return;
            RaycastHit hit;
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out hit, 100.0f))
            {
                if (hit.transform != null)
                {
                    try
                    {
                        Detail hitObj = hit.transform.GetComponent<Detail>();
                        UIManager.detailName.text = hitObj.Name;
                        UIManager.detailDescription.text = hitObj.Description;
                        panel.SetActive(true);
                    }
                    catch(Exception e) {
                        Debug.Log(e.Data);
                    }
                }
            }
        }
    }
}
