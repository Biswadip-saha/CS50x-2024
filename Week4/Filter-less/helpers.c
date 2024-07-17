#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed = 0, originalGreen = 0, originalBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            int avgGrayscale = round((float) (originalRed + originalGreen + originalBlue) / 3);
            image[i][j].rgbtRed = avgGrayscale;
            image[i][j].rgbtGreen = avgGrayscale;
            image[i][j].rgbtBlue = avgGrayscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed = 0, originalGreen = 0, originalBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            int sepiaRed =
                round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen =
                round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue =
                round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j] = image[i][j];
        }
    }

    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         int counter = 0;

    //         RGBTRIPLE pix1;
    //         RGBTRIPLE pix2;
    //         RGBTRIPLE pix3;
    //         RGBTRIPLE pix4;
    //         RGBTRIPLE pix6;
    //         RGBTRIPLE pix7;
    //         RGBTRIPLE pix8;
    //         RGBTRIPLE pix9;

    //         if (i - 1 < 0 || j - 1 < 0)
    //         {
    //             pix1.rgbtRed = 0;
    //             pix1.rgbtGreen = 0;
    //             pix1.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix1 = image2[i - 1][j - 1];
    //         }

    //         if (i - 1 < 0)
    //         {
    //             pix2.rgbtRed = 0;
    //             pix2.rgbtGreen = 0;
    //             pix2.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix2 = image2[i - 1][j];
    //         }

    //         if (i - 1 < 0 || j + 1 >= width)
    //         {
    //             pix3.rgbtRed = 0;
    //             pix3.rgbtGreen = 0;
    //             pix3.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix3 = image2[i - 1][j + 1];
    //         }

    //         if (j - 1 < 0)
    //         {
    //             pix4.rgbtRed = 0;
    //             pix4.rgbtGreen = 0;
    //             pix4.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix4 = image2[i][j - 1];
    //         }

    //         if (j + 1 >= width)
    //         {
    //             pix6.rgbtRed = 0;
    //             pix6.rgbtGreen = 0;
    //             pix6.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix6 = image2[i][j + 1];
    //         }

    //         if (i + 1 >= height || j - 1 < 0)
    //         {
    //             pix7.rgbtRed = 0;
    //             pix7.rgbtGreen = 0;
    //             pix7.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix7 = image2[i + 1][j - 1];
    //         }

    //         if (i + 1 >= height)
    //         {
    //             pix8.rgbtRed = 0;
    //             pix8.rgbtGreen = 0;
    //             pix8.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix8 = image2[i + 1][j];
    //         }

    //         if (j + 1 >= width || i + 1 >= height)
    //         {
    //             pix9.rgbtRed = 0;
    //             pix9.rgbtGreen = 0;
    //             pix9.rgbtBlue = 0;
    //             counter += 1;
    //         }
    //         else
    //         {
    //             pix9 = image2[i + 1][j + 1];
    //         }

    //         int blurRed = round((float) (pix1.rgbtRed + pix2.rgbtRed + pix3.rgbtRed + pix4.rgbtRed +
    //                                      image[i][j].rgbtRed + pix6.rgbtRed + pix7.rgbtRed +
    //                                      pix8.rgbtRed + pix9.rgbtRed) /
    //                             (9 - counter));
    //         int blurGreen = round((float) (pix1.rgbtGreen + pix2.rgbtGreen + pix3.rgbtGreen +
    //                                        pix4.rgbtGreen + image[i][j].rgbtGreen + pix6.rgbtGreen +
    //                                        pix7.rgbtGreen + pix8.rgbtGreen + pix9.rgbtGreen) /
    //                               (9 - counter));
    //         int blurBlue = round((float) (pix1.rgbtBlue + pix2.rgbtBlue + pix3.rgbtBlue +
    //                                       pix4.rgbtBlue + image[i][j].rgbtBlue + pix6.rgbtBlue +
    //                                       pix7.rgbtBlue + pix8.rgbtBlue + pix9.rgbtBlue) /
    //                              (9 - counter));
    //         image[i][j].rgbtRed = blurRed;
    //         image[i][j].rgbtGreen = blurGreen;
    //         image[i][j].rgbtBlue = blurBlue;
    //     }
    // }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rd = 0;
            int gr = 0;
            int bl = 0;
            int cnt = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if ((i + k) < height && (i + k) >= 0 && (j + l) >= 0 && (j + l) < width)
                    {
                        rd += image2[i + k][j + l].rgbtRed;
                        gr += image2[i + k][j + l].rgbtGreen;
                        bl += image2[i + k][j + l].rgbtBlue;
                        cnt++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) rd / cnt);
            image[i][j].rgbtGreen = round((float) gr / cnt);
            image[i][j].rgbtBlue = round((float) bl / cnt);
        }
    }
    return;
}
