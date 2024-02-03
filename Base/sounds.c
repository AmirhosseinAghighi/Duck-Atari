Mix_Music *menuMusic = NULL;
Mix_Music *gameMusic = NULL;
Mix_Music *highSpeedGameMusic = NULL;

Mix_Chunk *clickSoundEffect = NULL;
Mix_Chunk *rocketSoundEffect = NULL;

Mix_Chunk *laserSoundEffect = NULL;
Mix_Chunk *explosionSoundEffect = NULL;
Mix_Chunk *powerBulletSoundEffect = NULL;

Mix_Music *loadMusic(char *Address) {
    Mix_Music *music = Mix_LoadMUS( Address);
    if( music == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return NULL;
    }

    return music;
}

Mix_Chunk *loadSound(char *Address) {
    Mix_Chunk *sound = Mix_LoadWAV( Address );
    if( sound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return NULL;
    }

    return sound;
}


void DestroyMenuSounds();
void DestroyGameSounds();
void DestroyAnySound() {
    DestroyMenuSounds();
    DestroyGameSounds();
}

extern SettingsMenu *MusicStatus;
void playMenuMusic() {
    if (MusicStatus -> value == off || Mix_PlayingMusic()) {
        return;
    }
    if (menuMusic == NULL) {
        menuMusic = loadMusic("../sounds/menu.mp3");
        if (menuMusic == NULL) {
            SDL_Log("There was a problem in loading music of menu ! %s\n", SDL_GetError());
            return;
        }
    }


    if( Mix_PlayingMusic() == 0 ) {
        Mix_PlayMusic( menuMusic, -1 );
    }
}

void playGameMusic() {
    if (MusicStatus -> value == off || Mix_PlayingMusic()) {
        return;
    }
    if (gameMusic == NULL) {
        gameMusic = loadMusic("../sounds/song.mp3");
        if (gameMusic == NULL) {
            SDL_Log("There was a problem in loading music of menu ! %s\n", SDL_GetError());
            return;
        }
    }


    if( Mix_PlayingMusic() == 0 ) {
        Mix_VolumeMusic(50);
        Mix_PlayMusic( gameMusic, -1 );
    }
}

void playHighSpeedGameMusic() {
    if (MusicStatus -> value == off || Mix_PlayingMusic()) {
        return;
    }
    if (highSpeedGameMusic == NULL) {
        highSpeedGameMusic = loadMusic("../sounds/music2.mp3");
        if (highSpeedGameMusic == NULL) {
            SDL_Log("There was a problem in loading music of menu ! %s\n", SDL_GetError());
            return;
        }
    }

    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }

    if( Mix_PlayingMusic() == 0 ) {
        Mix_FadeInMusic(highSpeedGameMusic, -1, 1000);
        Mix_VolumeMusic(50);
    }
}


void DestroyMenuSounds() {
    if (menuMusic != NULL) {
        Mix_FreeMusic(menuMusic);
        menuMusic = NULL;
    }

    if (clickSoundEffect != NULL) {
        Mix_FreeChunk(clickSoundEffect);
        clickSoundEffect = NULL;
    }
}

void DestroyGameSounds() {
    if (gameMusic != NULL) {
        Mix_FreeMusic(gameMusic);
        gameMusic = NULL;
    }

    if (highSpeedGameMusic != NULL) {
        Mix_FreeMusic(highSpeedGameMusic);
        highSpeedGameMusic = NULL;
    }

    if (rocketSoundEffect != NULL) {
        Mix_FreeChunk(rocketSoundEffect);
        rocketSoundEffect = NULL;
    }

    if (laserSoundEffect != NULL) {
        Mix_FreeChunk(laserSoundEffect);
        laserSoundEffect = NULL;
    }

    if (explosionSoundEffect != NULL) {
        Mix_FreeChunk(explosionSoundEffect);
        explosionSoundEffect = NULL;
    }

    if (powerBulletSoundEffect != NULL) {
        Mix_FreeChunk(powerBulletSoundEffect);
        powerBulletSoundEffect = NULL;
    }
}

void stopMusic() {
    Mix_HaltMusic();
//    DestroySounds();
}

extern SettingsMenu *SoundEffectStatus;
void playClickSoundEffect() {
//    SDL_Log("%d %d", SoundEffectStatus -> value , off);
    if (SoundEffectStatus -> value == off)
        return;

    if (clickSoundEffect == NULL) {
        clickSoundEffect = loadSound("../sounds/click.mp3");
    }
    Mix_PlayChannel( -1, clickSoundEffect, 0 );
}

void playRocketSoundEffect() {
    if (SoundEffectStatus -> value == off)
        return;

    if (rocketSoundEffect == NULL) {
        rocketSoundEffect = loadSound("../sounds/rocket2.wav");
    }

    if (!Mix_Playing(1)) {
        Mix_FadeInChannel(1, rocketSoundEffect, -1, 0);
    }
}

//Mix_Chunk *laserSoundEffect = NULL;
//Mix_Chunk *explosionSoundEffect = NULL;
void playLaserSoundEffect() {
    if (SoundEffectStatus -> value == off)
        return;

    if (laserSoundEffect == NULL) {
        laserSoundEffect = loadSound("../sounds/laser.wav");
        Mix_VolumeChunk(laserSoundEffect, 60);
    }

    Mix_FadeInChannel(-1, laserSoundEffect, 0, 0);
}

void playExplosionSoundEffect() {
    if (SoundEffectStatus -> value == off)
        return;

    if (explosionSoundEffect == NULL) {
        explosionSoundEffect = loadSound("../sounds/explosion.wav");
        Mix_VolumeChunk(explosionSoundEffect, 60);
    }


    Mix_FadeInChannel(-1, explosionSoundEffect, 0, 0);
}

void playPowerBulletSoundEffect() {
    if (SoundEffectStatus -> value == off)
        return;

    if (powerBulletSoundEffect == NULL) {
        powerBulletSoundEffect = loadSound("../sounds/power.wav");
        Mix_VolumeChunk(powerBulletSoundEffect, 60);
    }


    Mix_FadeInChannel(-1, powerBulletSoundEffect, 0, 0);
}


void stopRocketSoundEffect() {
    if (Mix_Playing(1)) {
        Mix_FadeOutChannel(1, 100);
    }
}
