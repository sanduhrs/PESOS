<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Soundcloud App
 * @see http://soundcloud.com/you/apps
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Soundcloud',
  'class' => 'SoundcloudSilo',
);

/**
 * Class SoundcloudSilo.
 */
class SoundcloudSilo extends Silo {

  protected $title = 'Soundcloud';

  protected $scopes = array();

  public function connect() {
    parent::connect();

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
