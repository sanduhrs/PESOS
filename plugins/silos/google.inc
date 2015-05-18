<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Acquiring and using an API key
 * @see https://developers.google.com/+/api/oauth#apikey
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Google',
  'class' => 'GoogleSilo',
);

/**
 * Class GoogleSilo.
 */
class GoogleSilo extends Silo {

  protected $title = 'Google';

  protected $scopes = array('userinfo_email', 'userinfo_profile');

  public function connect() {
    parent::connect();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // This was a callback request from GitHub, get the token.
        $this->service->requestAccessToken($_GET['code']);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}
