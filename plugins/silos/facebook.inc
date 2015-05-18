<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Facebook',
  'class' => 'FacebookSilo',
);

/**
 * Class FacebookSilo.
 */
class FacebookSilo extends Silo {

  protected $title = 'Facebook';

  protected $scopes = array();

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