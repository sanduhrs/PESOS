<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a SoundCloud App
 * @see http://soundcloud.com/you/apps
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'SoundCloud',
  'class' => 'SoundCloudSilo',
);

/**
 * Class SoundCloudSilo.
 */
class SoundCloudSilo extends Silo {

  protected $title = 'SoundCloud';

  protected $scopes = array();

  public function authenticate() {
    parent::authenticate();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken($_GET['code']);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}
