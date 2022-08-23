/*
*  @file edgeColorPicker.cpp
*  Implements the edge color picker for CPSC 221 PA2.
*
*/

#include "edgeColorPicker.h"

/*
 *  Constructs a new EdgeColorPicker.
 *
 *  @param inputimage - original image to be colored
 *  @param b_color - color of the border
 *  @param width - width of the border to be painted
 *  @param s - seed point from flood fill configuration, must include original image color
 *  @param tol - tolerance threshold from flood fill configuration
 */
EdgeColorPicker::EdgeColorPicker(PNG& inputimage, RGBAPixel b_color, unsigned int width, PixelPoint s, double tol)
{
  // complete your implementation below
  referenceimg = inputimage;
  bordercolor = b_color;
  borderwidth = width;
  seed = s;
  tolerance = tol;

}

/*
*  Picks the color for pixel (x, y).
*  First determines whether p is a border pixel or not.
*
*  A border pixel is one which is within (<=) borderwidth of a non-fillable pixel
*  (i.e. at least one of the pixels within borderwidth of p will not be reached by
*  the filling algorithm.
*
*  A border pixel will be colored using the bordercolor.
*
*  A fillable non-border pixel will take the average color of all pixels within
*  borderwidth of p. Make sure that you are averaging from the original
*  image colors!
*
*  @param  p - The point for which you're picking a color
*  @return The color chosen for (p).
*/
RGBAPixel EdgeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  int top = p.y - borderwidth;
  unsigned bottom = p.y + borderwidth;
  int left = p.x - borderwidth;
  unsigned right = p.x + borderwidth;
  RGBAPixel* seed_p = referenceimg.getPixel(seed.x, seed.y);
  unsigned r = 0;
  unsigned g = 0;
  unsigned b = 0;
  unsigned a = 0;
  int cr = 0;
  int cg = 0;
  int cb = 0;
  int ca = 0;

  if (top < 0 || left < 0 || right > referenceimg.width() - 1 || bottom > referenceimg.height() - 1) {
    return bordercolor;
  }
  unsigned distance = borderwidth * borderwidth;
  
  for (unsigned y = (unsigned) top; y <= bottom; y++) {
    for (unsigned x = (unsigned) left; x <= right; x++) {
      unsigned dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y- y);
      if (dist <= distance) {
        RGBAPixel* pixel = referenceimg.getPixel(x, y);
        if (seed_p->dist(*pixel) >= tolerance) {
          return bordercolor;
        }
        RGBAPixel* add = referenceimg.getPixel(x, y);
        r += add->r;
        g += add->g;
        b += add->b;
        a += add->a;
        cr++;
        cg++;
        cb++;
        ca++;
      }
    }
  }
  RGBAPixel ret_rgb(r/cr, g/cg, b/cb, a/ca);
  return ret_rgb; // REPLACE THIS STUB
}
