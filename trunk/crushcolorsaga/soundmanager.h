#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <Phonon/MediaObject>

class SoundManager
{
    public:
        explicit SoundManager();

    static void PlayShoot();
    static void PlayJump();
    static void PlayExplosion();

private:
    Phonon::MediaObject* _player_shoot;
    Phonon::MediaObject* _player_jump;
    Phonon::MediaObject* _player_explosion;
};

#endif // SOUNDMANAGER_H
