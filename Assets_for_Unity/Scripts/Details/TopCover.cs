using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class TopCover : Detail
{
    void Start()
    {
        Name = "Верхняя крышка платформы";
        Description = "Быстросъемная крышка для доступа к внутренностям платформы. Также на крышку устанавливается камера.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
