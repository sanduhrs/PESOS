<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'GitHub',
  'class' => 'GithubSilo',
);

/**
 * Class GithubSilo.
 */
class GithubSilo extends Silo {

  protected $title = 'GitHub';

  protected $scopes = array('user', 'repo');

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
