#include "soundmanager.h"

SoundManager*g_SoundManager;
SoundManager::SoundManager()
{
    g_SoundManager = this;
    _player_shoot = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(":/models/snd_shoot"));
    _player_jump = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(":/models/snd_jump"));
    _player_explosion = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(":/models/snd_explosion"));
}

void SoundManager::PlayShoot()
{
    g_SoundManager->_player_shoot->stop();
    g_SoundManager->_player_shoot->play();
}

void SoundManager::PlayJump()
{
    g_SoundManager->_player_jump->stop();
    g_SoundManager->_player_jump->play();
}

void SoundManager::PlayExplosion()
{
    g_SoundManager->_player_explosion->stop();
    g_SoundManager->_player_explosion->play();
}
