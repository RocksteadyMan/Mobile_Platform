using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class BottomCover : Detail
{
    void Start()
    {
        Name = "Основание платформы";
        Description = "Является несущей деталью платформы. Имеет вырезы для установки ИК-датчиков, опорного ролика и деталей корпуса.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
