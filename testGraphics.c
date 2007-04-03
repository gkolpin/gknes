#include <SDL11/SDL.h>
#include <unistd.h>

int main(){

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Surface *surface = SDL_SetVideoMode(200, 200, 32, 0);

  

SDL_PixelFormat *fmt = surface->format;
SDL_LockSurface(surface);
Uint32 pixel = *((Uint32*)surface->pixels);
SDL_UnlockSurface(surface);

 Uint32 temp;
 Uint8 red;
 Uint8 blue;
 Uint8 green;
 Uint8 alpha;

/* Get Red component */
temp = pixel & fmt->Rmask;  /* Isolate red component */
temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
red = (Uint8)temp;

/* Get Green component */
temp = pixel & fmt->Gmask;  /* Isolate green component */
temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
green = (Uint8)temp;

/* Get Blue component */
temp = pixel & fmt->Bmask;  /* Isolate blue component */
temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
blue = (Uint8)temp;

/* Get Alpha component */
temp = pixel & fmt->Amask;  /* Isolate alpha component */
temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
alpha = (Uint8)temp;

printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", red, green, blue, alpha);






  //Try to draw a pixel

  int i;

  SDL_LockSurface(surface);

  for (i = 0; i < 10000; i++){

    Uint32 pixel = ((Uint32*)surface->pixels)[i];

    printf("%u\n", pixel);

    pixel = ~pixel;

    printf("%u\n", pixel);

    ((Uint32*)surface->pixels)[i] = pixel;

    printf("%u\n", ((Uint32*)surface->pixels)[i]);

  }

  SDL_UnlockSurface(surface);




fmt = surface->format;
SDL_LockSurface(surface);
pixel = *((Uint32*)surface->pixels);
SDL_UnlockSurface(surface);


/* Get Red component */
temp = pixel & fmt->Rmask;  /* Isolate red component */
temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
red = (Uint8)temp;

/* Get Green component */
temp = pixel & fmt->Gmask;  /* Isolate green component */
temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
green = (Uint8)temp;

/* Get Blue component */
temp = pixel & fmt->Bmask;  /* Isolate blue component */
temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
blue = (Uint8)temp;

/* Get Alpha component */
temp = pixel & fmt->Amask;  /* Isolate alpha component */
temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
alpha = (Uint8)temp;

printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", red, green, blue, alpha);














  //SDL_Flip(surface);

  //Set up rectangles
  SDL_Rect rect1;
  rect1.x = 0;
  rect1.y = 0;
  rect1.w = 0;
  rect1.h = 0;

  SDL_UpdateRects(surface, 1, &rect1);

  SDL_Flip(surface);

  sleep(2);

  SDL_Quit();

  

  return 0;
}
