<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Linkedin App
 * @see https://www.linkedin.com/developer/apps
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Linkedin',
  'class' => 'LinkedinSilo',
);

/**
 * Class LinkedinSilo.
 */
class LinkedinSilo extends Silo {

  protected $title = 'Linkedin';

  protected $scopes = array('r_basicprofile');

  public function connect() {
    parent::connect();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // Retrieve the CSRF state parameter.
        $state = isset($_GET['state']) ? $_GET['state'] : null;

        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken($_GET['code'], $state);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}
