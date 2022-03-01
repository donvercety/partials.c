#include "helpers.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            BYTE avg = (
                image[x][y].rgbtRed +
                image[x][y].rgbtGreen + 
                image[x][y].rgbtBlue
            ) / 3;

            image[x][y].rgbtRed   = avg;
            image[x][y].rgbtGreen = avg;
            image[x][y].rgbtBlue  = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            
            int r = (int) (
                0.393 * image[x][y].rgbtRed +
                0.769 * image[x][y].rgbtGreen +
                0.189 * image[x][y].rgbtBlue
            ); 

            int g = (int) (
                0.349 * image[x][y].rgbtRed +
                0.686 * image[x][y].rgbtGreen +
                0.168 * image[x][y].rgbtBlue 
            );

            int b = (int) (
                0.272 * image[x][y].rgbtRed +
                0.534 * image[x][y].rgbtGreen +
                0.131 * image[x][y].rgbtBlue 
            );
        
            image[x][y].rgbtRed   = r > 255 ? 255 : r;
            image[x][y].rgbtGreen = g > 255 ? 255 : g;
            image[x][y].rgbtBlue  = b > 255 ? 255 : b;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {
        for (int y = 0, len = width / 2; y < len; y++) {
            BYTE tempR = image[x][y].rgbtRed;
            BYTE tempG = image[x][y].rgbtGreen;
            BYTE tempB = image[x][y].rgbtBlue;

            image[x][y].rgbtRed   = image[x][width - y].rgbtRed;
            image[x][y].rgbtGreen = image[x][width - y].rgbtGreen;
            image[x][y].rgbtBlue  = image[x][width - y].rgbtBlue;

            image[x][width - y].rgbtRed   = tempR;
            image[x][width - y].rgbtGreen = tempG;
            image[x][width - y].rgbtBlue  = tempB;
        }
    }

    return;
}

// Blur image (box-blur)
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {

            copy[x][y].rgbtRed   = image[x][y].rgbtRed;
            copy[x][y].rgbtGreen = image[x][y].rgbtGreen;
            copy[x][y].rgbtBlue  = image[x][y].rgbtBlue;
        }
    }

    BYTE neighbors[9][3] = {
        {0,0,0}, {0,0,0}, {0,0,0}, // [0] [1] [2]
        {0,0,0}, {0,0,0}, {0,0,0}, // [3] [4] [5]
        {0,0,0}, {0,0,0}, {0,0,0}  // [6] [7] [8]
    };

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {

            char canGoUp    = x != 0;
            char canGoRight = y < width;
            char canGoDown  = x < height;
            char canGoLeft  = y != 0;

            
            if (canGoUp) {

                // find 0
                if (canGoLeft) {
                    neighbors[0][0] = copy[x - 1][y - 1].rgbtRed;
                    neighbors[0][1] = copy[x - 1][y - 1].rgbtGreen;
                    neighbors[0][2] = copy[x - 1][y - 1].rgbtBlue;
                }

                // find 1
                neighbors[1][0] = copy[x - 1][y].rgbtRed;
                neighbors[1][1] = copy[x - 1][y].rgbtGreen;
                neighbors[1][2] = copy[x - 1][y].rgbtBlue;

                // find 2
                if (canGoRight) {
                    neighbors[2][0] = copy[x - 1][y + 1].rgbtRed;
                    neighbors[2][1] = copy[x - 1][y + 1].rgbtGreen;
                    neighbors[2][2] = copy[x - 1][y + 1].rgbtBlue; 
                }
            }

            // find 3
            if (canGoLeft) {
                neighbors[3][0] = copy[x][y - 1].rgbtRed;
                neighbors[3][1] = copy[x][y - 1].rgbtGreen;
                neighbors[3][2] = copy[x][y - 1].rgbtBlue;   
            }

            // find 4 -- current
            neighbors[4][0] = copy[x][y].rgbtRed;
            neighbors[4][1] = copy[x][y].rgbtGreen;
            neighbors[4][2] = copy[x][y].rgbtBlue; 

            // find 5
            if (canGoRight) {
                neighbors[5][0] = copy[x][y + 1].rgbtRed;
                neighbors[5][1] = copy[x][y + 1].rgbtGreen;
                neighbors[5][2] = copy[x][y + 1].rgbtBlue;  
            }

            if (canGoDown) {

                // find 6
                if (canGoLeft) {
                    neighbors[6][0] = copy[x + 1][y - 1].rgbtRed;
                    neighbors[6][1] = copy[x + 1][y - 1].rgbtGreen;
                    neighbors[6][2] = copy[x + 1][y - 1].rgbtBlue;
                }

                // find 7
                neighbors[7][0] = copy[x + 1][y].rgbtRed;
                neighbors[7][1] = copy[x + 1][y].rgbtGreen;
                neighbors[7][2] = copy[x + 1][y].rgbtBlue;

                // find 8
                if (canGoRight) {
                    neighbors[8][0] = copy[x + 1][y + 1].rgbtRed;
                    neighbors[8][1] = copy[x + 1][y + 1].rgbtGreen;
                    neighbors[8][2] = copy[x + 1][y + 1].rgbtBlue;
                }
            }

            int avgR = 0, avgG = 0, avgB = 0;

            for (int i = 0; i < 9; i++) {
                avgR += neighbors[i][0];
                avgG += neighbors[i][1];
                avgB += neighbors[i][2];
            }

            image[x][y].rgbtRed   = (int) avgR / 9;
            image[x][y].rgbtGreen = (int) avgG / 9;
            image[x][y].rgbtBlue  = (int) avgB / 9;
        }
    }

    return;
}
