/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Queue>(config); // REPLACE THIS STUB
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Stack>(config); // REPLACE THIS STUB
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is removed
  * from the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the seed point,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is as follows:
  *        1. northern neighbour (up)
  *        2. eastern neighbour (right)
  *        3. southern neighbour (down)
  *        4. western neighbour (left)
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  vector<vector<int>> tracking;

  tracking.resize(config.img.height());
  for (unsigned i = 0; i < config.img.height(); i++) {
    tracking[i].resize(config.img.width());
    for (unsigned j = 0; j < config.img.width(); j++) {
      tracking[i][j] = 0; // 0 represents unprocessed
    }
  }

  os.Add(config.seedpoint);
  tracking[config.seedpoint.y][config.seedpoint.x] = 1;

  while (!os.IsEmpty()) {
    PixelPoint curr = os.Remove();
    *(config.img.getPixel(curr.x, curr.y)) = config.picker->operator()(curr);
    framecount++;

    if (framecount % config.frameFreq == 0) {
      anim.addFrame(config.img);
    }

    if ((int) curr.y - 1 >= 0 && tracking[curr.y - 1][curr.x] == 0) {
      PixelPoint pt(curr.x, curr.y - 1, *(config.img.getPixel(curr.x, curr.y - 1)));

      if (config.seedpoint.color.dist(*(config.img.getPixel(pt.x, pt.y))) <= config.tolerance) {
        os.Add(pt);
      }
      tracking[pt.y][pt.x] = 1;
      
    }
 
    if (curr.x + 1 < config.img.width() && tracking[curr.y][curr.x + 1] == 0) {
      PixelPoint pt(curr.x + 1, curr.y, *(config.img.getPixel(curr.x + 1, curr.y)));
      if (config.seedpoint.color.dist(*(config.img.getPixel(pt.x, pt.y))) <= config.tolerance) {
        os.Add(pt);
      }
      tracking[pt.y][pt.x] = 1;
    }

    if (curr.y + 1 < config.img.height() && tracking[curr.y + 1][curr.x] == 0) {
      PixelPoint pt(curr.x, curr.y + 1, *(config.img.getPixel(curr.x, curr.y + 1)));
      if (config.seedpoint.color.dist(*(config.img.getPixel(pt.x, pt.y))) <= config.tolerance) {
        os.Add(pt);
      }
      tracking[pt.y][pt.x] = 1;
    }

    if ((int) curr.x - 1 >= 0 && tracking[curr.y][curr.x - 1] == 0) {
      PixelPoint pt(curr.x - 1, curr.y, *(config.img.getPixel(curr.x - 1, curr.y)));
      if (config.seedpoint.color.dist(*(config.img.getPixel(pt.x, pt.y))) <= config.tolerance) {
        os.Add(pt);
      }
      tracking[pt.y][pt.x] = 1;
    }

  }

  anim.addFrame(config.img);

  return anim;
}
